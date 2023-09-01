#include <Arduino.h>
#include <FastLED.h>

#define LEDS_PER_STRIP 41
#define N_COUNTERS 11

#define SMM_IMPLEMENTATION
#define SMM_NO_SERIAL_CONTROLLER
#include "smm.h"
#include "pins.h"


class BeamBreak : public smm::Button {
	protected:
	volatile unsigned int m_count;

	public:
	BeamBreak(int pin) : smm::Button(pin), m_count(0) {}
	void onPress() {
		m_count += 1;
	}
	void onRelease() {}
	void reset() {
		m_count = 0;
	}
	unsigned int count() {
		return m_count;
	}
};


class CounterManager;
class Counter {
	protected:
  friend class CounterManager;
	BeamBreak *m_beam;
	CLEDController *m_controller;
	bool m_shouldReset;

	static CRGB leds[];

	void renderLevel(int level) {
		for (int i=0; i<LEDS_PER_STRIP; i++) {
			float x = ((float) i) / ((float) level);
			leds[LEDS_PER_STRIP-i] = 
				i<level ? CHSV(170, (1-(x*x))*255, 255) : CHSV(0, 0, 0);
		}
		m_controller->showLeds(128);
	}


	public:
	template <int dataPin, int clockPin, int m_beamPin>
	void setup() {
		m_beam = new BeamBreak(m_beamPin);
		m_controller = &FastLED.addLeds<APA102, dataPin, clockPin, BGR>(leds, LEDS_PER_STRIP);
		m_shouldReset = false;
	}

	void update() {
		show();
		m_shouldReset = (m_beam->count() > LEDS_PER_STRIP);
	}

	void show() {
		int count = m_beam->count();
		renderLevel(count);
	}

	void animateDrain() {
		int count = m_beam->count();
		for (int i=0; i<count; i++) {
			renderLevel(count - i);
			delay(5);
		}
	}

	void reset() {
		m_beam->reset();
		m_shouldReset = false;
	}

	bool shouldReset() {
		return m_shouldReset;
	}
};
CRGB Counter::leds[LEDS_PER_STRIP];


class CounterManager {
	protected:
	Counter counter[N_COUNTERS];

	public:
	void setup() {
		counter[0].setup<DATA0, CLOCK0, BEAM0>();
		counter[1].setup<DATA1, CLOCK1, BEAM1>();
		counter[2].setup<DATA2, CLOCK2, BEAM2>();
		counter[3].setup<DATA3, CLOCK3, BEAM3>();
		counter[4].setup<DATA4, CLOCK4, BEAM4>();
		counter[5].setup<DATA5, CLOCK5, BEAM5>();
		counter[6].setup<DATA6, CLOCK6, BEAM6>();
		counter[7].setup<DATA7, CLOCK7, BEAM7>();
		counter[8].setup<DATA8, CLOCK8, BEAM8>();
		counter[9].setup<DATA9, CLOCK9, BEAM9>();
		counter[10].setup<DATA10, CLOCK10, BEAM10>();
	}

  void testCounters() {
		for (int i=0; i<N_COUNTERS; i++) {
			for (int j=0; j<LEDS_PER_STRIP; j++) {
				counter[i].renderLevel(j);
				delay(5);
			}
		}
	}

	void update() {
		bool shouldReset = false;
		for (int i=0; i<N_COUNTERS; i++) {
			counter[i].update();
			shouldReset |= counter[i].shouldReset();
		}

		if (shouldReset) {
			for (int i=0; i<N_COUNTERS; i++) {
				counter[i].animateDrain();
				counter[i].reset();
			}
		}
	}
} counters;


void setup() {
	counters.setup();
	delay(250);
	counters.testCounters();
}


void loop() {
	counters.update();
}
