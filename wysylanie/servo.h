

enum ServoState {CALLIB, IDLE, IN_PROGRESS};
enum DetectorState{ACTIVE , INACTIVE};

void DetectorInit(void);
enum DetectorState eReadDetector(void);
void ServoInit(unsigned int uiServoFrequency);
void ServoCallib(void);
void ServoGoTo(unsigned int uiPosition);
