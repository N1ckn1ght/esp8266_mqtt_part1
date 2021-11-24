import time
import paho.mqtt.client as paho
import json

client = paho.Client('foo')
client.connect('broker.emqx.io', 1883, 60)

client.loop_start()
client.publish('foo/command', 'zxc')

time.sleep(30)
client.disconnect()
