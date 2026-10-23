# Leanbot contain Green pollution at B1
# Start
# - Leanbot at CRL
# - Pollution: Green at B1
# Leanbot steps
# - Follow line to B1
# - Push Pollution into Containment B
# - Mission end (Leanbot stops at Containment B)


# #include <Leanbot.h>
from pyLeanbot2 import *
import SynapseCity                     # Synapse City field simulation

speed = 2000

def setupSynapseCity():
    # setup Pollution Blocks
    SynapseCity.setBlocks("""
        B1  Green
    """)

def setup():
    setupSynapseCity()
    Leanbot.begin()

def loop():
    LbMission.beginDigitalTwin('SynapseCity.01')
    FromCRLtoB1()
    PushPollutionB1()
    LbMission.end()
    SynapseCity.getFinalScore()

def FromCRLtoB1():
    Forward(speed, 110)                            # Go  to the line.
    Rotate(-speed, 30)                             # Turn Left
    followLineMultipleJunctions(4)                 # Move 4 Junctions
    goToJunction()
    Rotate(speed, 53)                              # Turn right
    followLineMultipleJunctions(1)                 # Move 1 Junctions
    goToJunction()

def PushPollutionB1():
    Rotate(speed, 22)                              # Turn right
    Forward(speed, 32)                             # Run closer to the block at B1
    Rotate(speed/4, 50)                            # Move the green block into containment B

def Forward(speed, distanceMm):
    LbMotion.runLR(speed, speed)                  # Move forward with given speed
    LbMotion.waitDistanceMm(distanceMm)           # Wait until distance is reached
    LbMotion.stopAndWait()                        # Stop and wait

def Backward(speed, distanceMm):
    LbMotion.runLR(-speed, -speed)                # Move backward with given speed
    LbMotion.waitDistanceMm(distanceMm)           # Wait until distance is reached
    LbMotion.stopAndWait()                        # Stop and wait

def Rotate(speed, deg):
    LbMotion.runLR(speed, -speed)                 # Rotate robot in place
    LbMotion.waitRotationDeg(deg)                 # Wait until rotation angle is reached
    LbMotion.stopAndWait()                        # Stop and wait

def followLineDistance(distanceMm):
    targetMm = distanceMm + LbMotion.getDistanceMm() # Calculate targ et distance

    while LbMotion.getDistanceMm() < targetMm: 				# Continue until target distance is reached
        runFollowLine()                             				# Run line following logic

def runFollowLine():
    #LbRGB.fillColor(CRGB.Black) # Off RGB
    lineValue = LbIRLine.read()                # Read IR line sensor value
    LbIRLine.displayOnRGB(CRGB.DarkCyan)          # Display sensor status on RGB LED

    match lineValue:

        case 0b0100:                                 # .o..
            LbMotion.runLR(+speed/2, +speed)          # Adjust slightly to the left

        case 0b0010:                                 # ..o.
            LbMotion.runLR(+speed, +speed/2)          # Adjust slightly to the right

        case 0b1100:                                 # oo..
            LbMotion.runLR(     0, +speed)            # Strong left correction

        case 0b0011:                                 # ..oo
            LbMotion.runLR(+speed, 0)                 # Strong right correction

        case 0b1000:                                 # o...
            LbMotion.runLR(-speed/2, +speed/2)        # Sharp left turn

        case 0b0001:                                 # ...o
            LbMotion.runLR(+speed/2, -speed/2)        # Sharp right turn

        case _:
            LbMotion.runLR(+speed, +speed)            # Go straight

def followLineUntilJunction():
    while LbIRLine.read() != 0b1111:            # Continue until full junction is detected
        runFollowLine()                             # Run line following logic

def goToJunction():
    followLineUntilJunction()                     # Continue until junction is detected
    followLineDistance(5)                        # Move forward to the purple block
    LbMotion.stopAndWait()                        # Stop and wait

def followLineMultipleJunctions(junctionCount):
    for i in range(junctionCount):
        followLineDistance(30)
        followLineUntilJunction()

# Main Python code
setup()
loop()
