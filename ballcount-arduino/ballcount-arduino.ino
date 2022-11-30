#include <Arduino.h>
#include <FastLED.h>

class Counter {
	protected:
	CLEDController *controller;
	int count;

	static CRGB leds[];


	public:
	template<int dataPin, int clockPin>
	void setup() {
		controller = &FastLED.addLeds<APA102, dataPin, clockPin, BGR>(leds, 60);
		count = 0;
	}

	void show() {
		for (int i=0; i<60; i++) {
			leds[i] = i<count ? CHSV((255*i/60), 255, 255) : CHSV(0, 0, 0);
		}
		controller->showLeds(128);
	}

	void increment() {
		count += 1;
	}

	void reset() {
		count = 0;
	}
};

CRGB Counter::leds[60];


Counter counter[3];


void setup() {
	counter[0].setup<A0,A1>();
	counter[1].setup<4,5>();
	counter[2].setup<6,7>();
}

void loop() {
	for (int i=0; i<3; i++) {
		for (int j=0; j<60; j++) {
			counter[i].increment();
			counter[0].show();
			counter[1].show();
			counter[2].show();
			delay(10);
		}
		counter[i].reset();
	}
}
