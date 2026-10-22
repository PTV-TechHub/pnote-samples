from pyLeanbot import *
# PNote version (Pythaverse2026#652): same as ../virtualleanbot/msNumberGrid.py without speedUp, which PNote's pyLeanbot does not accept.

MISSION = 'msNumberGrid'
TOTAL_LAPS = 13

Leanbot.begin()
print('Starting mission:', MISSION)
LbMission.beginDigitalTwin(MISSION)   # PNote's pyLeanbot takes only the mission id (no speedUp)

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
