extern void digitalWrite(uint8_t pin, uint8_t state);
extern void pinMode(uint8_t pin, uint8_t mode);
extern uint8_t getPortpin(uint8_t pin);
extern uint8_t getPort(uint8_t pin);

//pinMode(pin#, mode)
#define OUTPUT 1
#define INPUT 2
#define INPUT_PULLUP 3

//digitalWrite(pin#,state)
#define HIGH 1
#define LOW 0
#define TOGGLE 3
