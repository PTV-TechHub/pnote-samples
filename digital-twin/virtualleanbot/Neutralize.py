# Leanbot pick up Neutralize at S3 and contain Blue pollution at E2
# Start
# - Leanbot at CRL
# - Pollution: Blue at E2
# - Neutralize at S3
# Leanbot steps
# - Follow line to S3
# - Pick up Neutralize at S3
# - Follow line to E2
# - Push Pollution into Containment E
# - Drop Neutralize into Containment E
# - Mission end (Leanbot stops at Containment E)


# #include <Leanbot.h>
from pyLeanbot2 import *
import SynapseCity                     # Synapse City field simulation

speed = 2000

def setupSynapseCity():
    # setup Neutralizer Blocks
    SynapseCity.setBlocks("""
        S3  Blue
    """)
    # setup Pollution Blocks
    SynapseCity.setBlocks("""
        E2  Blue
    """)

def setup():
    setupSynapseCity()
    Leanbot.begin()

def loop():
    LbMission.beginDigitalTwin('SynapseCity.01')
    FromCRLtoS3()
    PickupNeutralizeS3()                     # neutralize rides along to E2
    FromS3toE2()
    PushPollutionE2()
    DropNeutralizeE2()
    LbMission.end()
    SynapseCity.getFinalScore()

def FromCRLtoS3():
    Forward(speed, 110)                            # Go  to the line.
    Rotate(-speed, 108)                            # Turn Left
    followLineMultipleJunctions(2)                 # Move 2 Junctions
    goToJunction()

def PickupNeutralizeS3():
    LbGripper.close(50)                            # Close

def FromS3toE2():
    Rotate(speed, 53)                              # Turn right
    followLineMultipleJunctions(2)                 # Move 2 Junctions
    goToJunction()
    Rotate(speed, 53)
    followLineMultipleJunctions(2)                 # Move 2 Junctions
    goToJunction()
    Rotate(speed, 25)                              # Turn right

def PushPollutionE2():
    Forward(speed, 150)

def DropNeutralizeE2():
    LbGripper.open()

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
