from pyLeanbot import *

MISSION = 'msNumberGrid'
SPEED_UP = 1
TOTAL_LAPS = 13

Leanbot.begin()
print('Starting mission:', MISSION)
LbMission.beginDigitalTwin(MISSION, speedUp=SPEED_UP)

for lap in range(1, TOTAL_LAPS + 1):
    print('Lap', lap, 'of', TOTAL_LAPS)

    LbMotion.runLR(2000, 2000)
    LbDelay(1000)
    LbMotion.stopAndWait()

    LbMotion.runLR(2000, -2000)
    LbDelay(500)
    LbMotion.stopAndWait()

LbMission.end()
print('Mission complete after', TOTAL_LAPS, 'laps')
