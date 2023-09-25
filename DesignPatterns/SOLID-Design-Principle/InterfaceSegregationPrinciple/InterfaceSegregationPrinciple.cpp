//
// Created by Amit Kumar on 24/09/23.
//

#include <iostream>
using namespace std;

class PhotoManager {
public:
    virtual void takePhoto() = 0;
};

class PowerManager {
public:
    virtual void powerOn() = 0;
    virtual void powerOff() = 0;
};

class MusicManager {
public:
    virtual void playMusic() = 0;
};

class BatteryManager {
public:
    virtual void chargeBattery() = 0;
};

class Phone: public PhotoManager, public PowerManager, public MusicManager, public BatteryManager{
public:
    void powerOn() override {
        cout << "power on" << endl;
    }

    void powerOff() override {
        cout << "power off" << endl;

    }

    void playMusic() override {
        cout << "playing music " << endl;

    }

    void chargeBattery() override {
        cout << "charging battery" << endl;

    }

    void takePhoto() override {
        cout << "clicking photo" << endl;
    }
};

class Camera: public PowerManager, public BatteryManager, public PhotoManager{
public:
    void powerOn() override {
        cout << "power on" << endl;
    }

    void powerOff() override {
        cout << "power off" << endl;

    }

    void chargeBattery() override {
        cout << "charging battery" << endl;

    }

    void takePhoto() override {
        cout << "clicking photo" << endl;
    }
};

int main() {
    Phone *phone = new Phone();
    Camera *camera = new Camera();
    return 0;
}