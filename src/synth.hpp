#ifndef synth_hpp
#define synth_hpp

#include <stdio.h>
#include <vector>
#include <array>
#include "ofMain.h"
#include "ofxMaxim.h"

//--------------------------------------------------------------
class Waveform
{
protected:
    // Using references to avoid dealing with raw pointers!
    std::vector<float>& frequencies;
    std::vector<int>& triggers;
    std::vector<maxiEnv>& envelopes;
    
    float sum = 0.0f;
    std::array<maxiOsc, 18> oscillators;
    
    Waveform(std::vector<float>& frequencies, std::vector<int>& triggers, std::vector<maxiEnv>& envelopes)
    : frequencies{frequencies}, triggers{triggers}, envelopes{envelopes} {}
    
public:
    // C++ guidelines say that "A class with a virtual function
    // should have a virtual or protected destructor"
    virtual ~Waveform() {}
    virtual float output() = 0;
};

//--------------------------------------------------------------
class Sines : public Waveform
{
public:
    Sines(std::vector<float>& frequencies, std::vector<int>& triggers, std::vector<maxiEnv>& envelopes)
    : Waveform(frequencies, triggers, envelopes) {}
    
    float output() override;
};

//--------------------------------------------------------------
class Saws : public Waveform
{
public:
    Saws(std::vector<float>& frequencies, std::vector<int>& triggers, std::vector<maxiEnv>& envelopes)
    : Waveform (frequencies, triggers, envelopes) {}
    
    float output() override;
};

//--------------------------------------------------------------
class Squares : public Waveform
{
public:
    Squares(std::vector<float>& frequencies, std::vector<int>& triggers, std::vector<maxiEnv>& envelopes)
    : Waveform(frequencies, triggers, envelopes) {}
    
    float output() override;
};

//--------------------------------------------------------------
class Triangles : public Waveform
{
public:
    Triangles(std::vector<float>& frequencies, std::vector<int>& triggers, std::vector<maxiEnv>& envelopes)
    : Waveform(frequencies, triggers, envelopes) {}
    
    float output() override;
};

//--------------------------------------------------------------
class Synth
{
public:
    Synth();
    void update();
    void keyPressed(int key);
    void keyReleased(int key);
    bool preset1 = true;
    bool preset2, preset3, preset4 = false;
    float output();
private:
    // Using pointers to enable polymorphism
    std::array<std::unique_ptr<Waveform>, 4> waveform;
    std::array<float, 4> channel = {};      // zero all elements; better in some situations
    
    std::vector<maxiEnv> envelopes;
    std::vector<float> frequencies;
    std::vector<int> triggers;
    
    int   attack  = 10;
    int   decay   = 50;
    float sustain = 0.5;
    int   release = 3500;
    
    convert converter;
    std::vector<char> letters = {'a', 'w', 's', 'e', 'd', 'f', 't', 'g', 'y', 'h', 'u', 'j', 'k'};
    
    void changeOctave(int key);
    int octave = 1;
    bool useExtended = false;
};

#endif /* synth_hpp */
