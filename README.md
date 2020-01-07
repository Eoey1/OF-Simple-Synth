# OF-Simple-Synth
A simple polyphonic synthesizer that you can play with your computer keyboard

This is ideal for testing when working with audio in openFrameworks.  You can add it to your project by simply including
the header file, instantiating the synth in ofApp.h and then adding the following methods to your OF app:

Add synth.update() to the update() function, synth.output() to the audioOut() function, synth.keyPressed(key) to the 
keyPressed(int key) function and synth.keyReleased(key) to the keyReleased(int key) function.

You can extend the length of the keyboard by pressing 'Enter' and change octave with the arrow keys.  Use number keys 1-4
to toggle different various waveforms.


