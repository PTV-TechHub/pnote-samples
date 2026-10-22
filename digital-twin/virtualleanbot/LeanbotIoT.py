# Demo: write/read an OpenRemote attribute and print the result.
from pyLeanbot import *

ASSET_ID = '33khwmcNaidrPJ2oZpcgde'
ATTRIBUTE = 'notes'
MESSAGE = 'Hello from LeanbotIoT'

Leanbot.begin()
LbMission.beginDigitalTwin('msNumberGrid', speedUp=1)

print('Writing:', MESSAGE)
write_status = LbIoT.write(ASSET_ID, ATTRIBUTE, MESSAGE)
print('Write status:', write_status)

value = LbIoT.read(ASSET_ID, ATTRIBUTE)
print('Read value:', value)

LbMission.end()
