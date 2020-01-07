#include "synth.hpp"

//--------------------------------------------------------------
float Sines::output()
{
    for (int i = 0; i < envelopes.size(); i++) {
        sum += envelopes[i].adsr(oscillators[i].sinewave(frequencies[i]), triggers[i]);
    }

    sum /= envelopes.size();
    return sum;
}

//--------------------------------------------------------------
float Saws::output()
{
    for (int i = 0; i < envelopes.size(); i++) {
        sum += envelopes[i].adsr(oscillators[i].saw(frequencies[i]), triggers[i]);
    }
    
    sum /= envelopes.size();
    return sum;
}

//--------------------------------------------------------------
float Squares::output()
{
    for (int i = 0; i < envelopes.size(); i++) {
        sum += envelopes[i].adsr(oscillators[i].square(frequencies[i]), triggers[i]);
    }
    
    sum /= envelopes.size();
    return sum;
}

//--------------------------------------------------------------
float Triangles::output()
{
    for (int i = 0; i < envelopes.size(); i++) {
        sum += envelopes[i].adsr(oscillators[i].triangle(frequencies[i]), triggers[i]);
    }
    
    sum /= envelopes.size();
    return sum;
}

//--------------------------------------------------------------
Synth::Synth()
{
    for (int i = 0; i < 13; i++) {
        envelopes.push_back(maxiEnv{});
        frequencies.push_back(converter.mtof(60 + i));
        triggers.push_back(0);
    }
    
    waveform[0] = make_unique<Sines>(frequencies, triggers, envelopes);
    waveform[1] = make_unique<Saws>(frequencies, triggers, envelopes);
    waveform[2] = make_unique<Squares>(frequencies, triggers, envelopes);
    waveform[3] = make_unique<Triangles>(frequencies, triggers, envelopes);
}

//--------------------------------------------------------------
void Synth::update()
{
    for (auto& env : envelopes) {
        env.setAttack(attack);
        env.setDecay(decay);
        env.setSustain(sustain);
        env.setRelease(release);
    }
}

//--------------------------------------------------------------
float Synth::output()
{
    if (preset1) {
        channel[0] = waveform[0]->output();
    } else {
        channel[0] = 0;
    }
    
    if (preset2) {
        channel[1] = waveform[1]->output() * 0.5;
    } else {
        channel[1] = 0;
    }
    
    if (preset3) {
        channel[2] = waveform[2]->output() * 0.3;
    } else {
        channel[2] = 0;
    }
    
    if (preset4) {
        channel[3] = waveform[3]->output();
    } else {
        channel[3] = 0;
    }
    
    return channel[0] + channel[1] + channel[2] + channel[3];
}

//--------------------------------------------------------------
void Synth::keyPressed(int key)
{
    for (auto& elem : letters) {
        // if the current index is needed:
        auto i = &elem - &letters[0];
        
        if (key == letters[i]) {
            triggers[i] = 1;
        }
    }    
    
    if (key == '1') {
        preset1 = !preset1;
        cout << "sines" << endl;
    }
    
    if (key == '2') {
        preset2 = !preset2;
        cout << "saws" << endl;
    }
    
    if (key == '3') {
        preset3 = !preset3;
        cout << "squares" << endl;
    }
    
    if (key == '4') {
        preset4 = !preset4;
        cout << "triangles" << endl;
    }
    
    if (key == OF_KEY_RETURN) {
        useExtended = !useExtended;
        
        if (useExtended) {
            for (int i = 0; i < 5; i++) {
                envelopes.push_back(maxiEnv{});
                
                if (octave == 0) {
                    frequencies.push_back(converter.mtof(61 + i));
                } else if (octave == 1) {
                    frequencies.push_back(converter.mtof(73 + i));
                } else if (octave == 2) {
                    frequencies.push_back(converter.mtof(85 + i));
                }
                
                triggers.push_back(0);
            }
            
            letters.push_back('o');
            letters.push_back('l');
            letters.push_back('p');
            letters.push_back(';');
            letters.push_back(39);      // Have to use ASCII for apostrophe character
        }
        
        else if (!useExtended) {
            envelopes.erase(envelopes.begin() + 13, envelopes.begin() + 18);
            frequencies.erase(frequencies.begin() + 13, frequencies.begin() + 18);
            triggers.erase(triggers.begin() + 13, triggers.begin() + 18);
            letters.erase(letters.begin() + 13, letters.begin() + 18);
        }
    }
    
    if (key == OF_KEY_UP || key == OF_KEY_DOWN) {
        changeOctave(key);      
    }
}

//--------------------------------------------------------------
void Synth::keyReleased(int key)
{
    for (auto& elem : letters) {
        auto i = &elem - &letters[0];
        
        if (key == letters[i]) {
            triggers[i] = 0;
        }
    }
}

//--------------------------------------------------------------
void Synth::changeOctave(int key) {
    
    if (key == OF_KEY_UP  && octave != 2) {
        octave += 1;
    } else if (key == OF_KEY_DOWN && octave != 0) {
        octave -= 1;
    }
    
    for (int i = 0; i < frequencies.size(); i++) {
        if (octave == 0) {
            frequencies[i] = (converter.mtof(48 + i));
        } else if (octave == 1) {
            frequencies[i] = (converter.mtof(60 + i));
        } else if (octave == 2) {
            frequencies[i] = (converter.mtof(72 + i));
        }
    }
}
