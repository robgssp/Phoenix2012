#include "Dumper.h"

struct IntRange {
	int low, high;
	bool contains (int val) { return val > low && val < high; }
	int midpoint() { return (high - low) / 2; }
};

struct IntakeState {
	long startTime;
	int endPos;
};

static IntRange balls[] = {{50, 150}, {150, 250}, {250, 350}};

Dumper::Dumper(int frontRollerPort, int rearRollerPort, int infraPort, 
			   Robot *robot) {
	this->robot_ = robot;
	this->frontRoller_ = new Relay(frontRollerPort);
	this->rearRoller_ = new Relay(rearRollerPort);
	this->infra_ = new AnalogChannel(infraPort);
	this->targetRange_ = NULL;
}

/**
 * Queries how many balls are contained inside the dumper
 */
int Dumper::contains() {
	int dist = infra_->GetValue();
	int i;
	for(i = 3; balls[i - 1].contains(dist); --i);
	return i;
}

/**
 * Runs dumper motors in deployment mode
 */
void Dumper::deploy() {
	frontRoller_->Set(Relay::kForward);
	rearRoller_->Set(Relay::kForward);
}

void Dumper::setDeployTarget() {
	int dist = infra_->GetValue();
	for(int i = 0; i < 3; ++i) {
		if(balls[i].contains(dist)) {
			targetRange_ = &balls[i];
		}
	}
}

/**
 * Deploy a single ball.
 * Returns: false until ball is deployed, then True.
 */
bool Dumper::deployOne() {
	int dist = infra_->GetValue();
	if(!targetRange_) setDeployTarget();
	int target = targetRange_->midpoint();
	deploy();
	if(dist < target) {
		targetRange_ = NULL;
		return true;
	} else return true;
}

void Dumper::intake() {
	
}
