# Demo: follow the perimeter lines around SynapseCity map and back

from pyLeanbot2 import *
import SynapseCity

speed = 1900


def setup():
    Leanbot.begin()


def loop():
    LbMission.beginDigitalTwin('SynapseCity.01')
    Forward(-speed, 300)               # back toward perimeter
    Rotate(-speed, 45 - 15)            # align Leanbot heading to black line

    for i in range(20):                # go through 20 junctions
        followLineUntilJunction(20)
    LbMotion.stopAndWait()

    Rotate(-speed, 180 - 30)           # turn back

    for i in range(19):                # go through 20 junctions
        followLineUntilJunction(20)
    LbMotion.stopAndWait()

    LbMission.end()


def Forward(speed, distanceMm):
    LbMotion.runLR(speed, speed)
    LbMotion.waitDistanceMm(distanceMm)
    LbMotion.stopAndWait()


def Rotate(speed, deg):
    LbMotion.runLR(speed, -speed)
    LbMotion.waitRotationDeg(deg)
    LbMotion.stopAndWait()


def runFollowLine():
    lineValue = LbIRLine.read()

    match lineValue:
        case 0b_0100:
            LbMotion.runLR(speed/2, speed)
        case 0b_0010:
            LbMotion.runLR(speed, speed/2)
        case 0b_1100:
            LbMotion.runLR(0, speed)
        case 0b_0011:
            LbMotion.runLR(speed, 0)
        case 0b_1000:
            LbMotion.runLR(-speed/2, speed/1)
        case 0b_0001:
            LbMotion.runLR(speed/1, -speed/2)
        case _:
            LbMotion.runLR(speed, speed)


def followLineUntilJunction(extraDistanceMm = 0):
    while LbIRLine.read() != 0b_1111:
        runFollowLine()
    LbMotion.waitDistanceMm(extraDistanceMm)    # continue straight over black junction marker


# Main Python code
setup()
loop()