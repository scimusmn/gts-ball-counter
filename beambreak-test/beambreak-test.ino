#include <Arduino.h>

#define SMM_IMPLEMENTATION
#include "smm.h"


#define BEAM 14

class BeamBreak : public smm::Button
{
	public:
	BeamBreak() : smm::Button(BEAM) {}
	void onPress() {
		SmmSerial.send("beam-break", "0");
	}
	void onRelease() {
		SmmSerial.send("beam-break", "1");
	}
} beamBreak;

void setup() {
	SmmSerial.begin();
	SmmSerial.send("ready", 1);
}

void loop() {}
