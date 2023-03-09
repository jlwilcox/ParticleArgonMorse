// We define LED to be D7 which is connected to the built in LED on the Particle Argon. The button is connected to D2 in this instance.

const pin_t LED = D7;
const pin_t BUTTON = D2;

const int UNIT_LENGTH = 65; // Length of a Morse unit in ms
const int DASH_UNITS = 3;
const int DOT_UNITS = 1;
const int COMPONENT_SEPARATOR_UNITS = 1;
const int CHARACTER_SEPARATOR_UNITS = 3;

const char MORSE[26][5]  = { { 'A', 1, 10, 0, 0}, // 1 = dot, 10 = dash, 0 = nothing
                        { 'B', 10, 1, 1, 1 },
                        { 'C', 10, 1, 10, 1 },
                        { 'D', 10, 1, 1, 0 },
                        { 'E', 1, 0, 0, 0 },
                        { 'F', 1, 1, 10, 1 },
                        { 'G', 10, 10, 1, 0 },
                        { 'H', 1, 1, 1, 1 },
                        { 'I', 1, 1, 0, 0 },
                        { 'J', 1, 10, 10, 10 },
                        { 'K', 10, 1, 10, 0 },
                        { 'L', 1, 10, 1, 1 },
                        { 'M', 10, 10, 0, 0 },
                        { 'N', 10, 1, 0, 0 },
                        { 'O', 10, 10, 10, 0 },
                        { 'P', 1, 10, 10, 1 },
                        { 'Q', 10, 10, 1, 10 },
                        { 'R', 1, 10, 1, 0 },
                        { 'S', 1, 1, 1, 0 },
                        { 'T', 10, 0, 0, 0 },
                        { 'U', 1, 1, 10, 0 },
                        { 'V', 1, 1, 1, 10 },
                        { 'W', 1, 10, 10, 0 },
                        { 'X', 10, 1, 1, 10 },
                        { 'Y', 10, 1, 10, 10 },
                        { 'Z', 10, 10, 1, 1 } };

// allows code to run before the cloud is connected
SYSTEM_THREAD(ENABLED);

// The setup() method is called once when the device boots.
void setup() {
	// In order to set a pin, you must tell Device OS that the pin is 
	// an OUTPUT pin. This is often done from setup() since you only need 
	// to do it once.
	pinMode(LED, OUTPUT);
	pinMode(BUTTON, INPUT);
}

// The loop() method is called frequently.
void loop() {
    char* morseString = "JAMES"; // Only uppercase supported

    // Loop until the button is pressed, when it is then we can call the blinkString function to blink the morse code
    if (digitalRead(BUTTON) == HIGH)
    {
        blinkString(morseString);
    }

}

void blinkString(char* string)
{
    int length = strlen(string);
    
    // Iterate through name until we get to the null character (end of string)
    for (int i = 0; i < length; i++)
    {
        blinkLetter(string[i]);
        
        if (i < length - 1)
        {
            // We're between characters, delay for 3 units
            morseDelay(CHARACTER_SEPARATOR_UNITS);
        }
    }
}

void blinkLetter(char letter)
{
    const char* letterMorse = MORSE[letter - 'A']; // This will offset the ASCII value to the start of the morese array
    
    int length = getMorseLength(letterMorse);
    
    // Itererate through morse values until we get to 0 (meaning no more units) or length of array
    for (int i = 0; i < length; i++)
    {
        if (letterMorse[i] == 1)
        {
            // Dot
            blinkMorseUnit(DOT_UNITS);
        }
        else if (letterMorse[i] == 10)
        {
            // Dash
            blinkMorseUnit(DASH_UNITS);
        }
        
        if (i < length - 1)
        {
            // We are between a dot and a dash, we must add a 1 unit delay
            morseDelay(COMPONENT_SEPARATOR_UNITS);
        }
    }
}

int getMorseLength(const char* letterMorse)
{
    int length = 0;
    
    for (int i = 0; i < 5; i++)
    {
        if (letterMorse[i] > 0)
        {
            length++;
        }
        else
        {
            break;
        }
    }
    
    return length;
}

void blinkMorseUnit(int units)
{
    digitalWrite(LED, HIGH);
    morseDelay(units);
    digitalWrite(LED, LOW);
}

void morseDelay(int units) {
    delay(UNIT_LENGTH * units);
}