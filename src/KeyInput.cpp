/**
 * Keyboard Input implementation
 */

#include "KeyInput.h"

KeyInput& KeyInput::Get()
{
  static KeyInput instance;

  return instance;
}


void KeyInput::Update()
{
  for(auto& [key, keypress] : keys)
  {
    bool down = sf::Keyboard::isKeyPressed(key);

    keypress.pressed = false;
    if(down && !keypress.isdown)
      keypress.pressed = true;

    keypress.isdown = down;
  }
}


bool KeyInput::KeyPressed(sf::Keyboard::Key key)
{
  bool result = false;
  try {
    result = keys.at(key).pressed;
  } catch(...) {
    keys.emplace(key, Keystroke{false,false});
    return false;
  }

  keys.at(key).pressed = false; // Eat input
  return result;
}


bool KeyInput::Return()
{
  return KeyPressed(sf::Keyboard::Key::Return);
}
