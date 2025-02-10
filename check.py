from pynput.keyboard import Controller, Key
import time

# Create a keyboard controller object
keyboard = Controller()

time.sleep(5)  # Wait for a few seconds to switch to the target window

for i in range(200):
    time.sleep(0.3)  # Delay between iterations
    
    if i % 20 == 0:
        # Type "Don't go up"
        keyboard.type("Uper na ja bhai")
        keyboard.press(Key.enter)
        keyboard.release(Key.enter)
    
    # Type "Furrrrr"
    keyboard.type("🚀🚀🚀")
    keyboard.press(Key.enter)
    keyboard.release(Key.enter)
