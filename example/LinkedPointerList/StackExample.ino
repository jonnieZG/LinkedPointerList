/**
 * This example pushes between 3 and 9 random numbers to the stack and retrieves them in the reverse order.
 */
#include <Arduino.h>
#include "LinkedPointerList.h"

void setup() {
	Serial.begin(115200);
	Serial.println("\n\nLinkedPointerList\n");

}

void loop() {
	// Make the stack
	LinkedPointerList<int> stack;

	// Decide how many numbers will it generate
	int count = random(3, 10);
	
	for (int i = 0; i < count; i++) {
		// Create a new int (it will have to be explicitly removed after use!)
		int *value = new int;
		// Store a random value into it 
		*value = random(1000); 
		// Push it to the stack
		stack.unshift(value);
		Serial.printf("Pushed value: %d\n", *value);
	}

	Serial.println();

	while (stack.size() > 0) {
		// Retrieve the latest value from the stack
		int *value = stack.shift();
		Serial.printf("Fetched value: %d\n", *value);
		// Delete the int object!
		delete value;
	}

	Serial.println();
	delay(2000);
}
