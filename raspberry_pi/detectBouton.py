import paho.mqtt.client as mqtt
import appel_pouvoirs

broker_address = "192.168.1.109"
client = mqtt.Client()

def on_message(client, userdata, msg):
    topic = msg.topic
    if topic == "gant1/index":
        appel_pouvoirs.BP_index()
    elif topic == "gant1/majeur":
        appel_pouvoirs.BP_majeur()
    elif topic == "gant1/annulaire":
        appel_pouvoirs.BP_annulaire()
    elif topic == "gant1/auriculaire":
        appel_pouvoirs.BP_auriculaire()

client.on_message = on_message
client.connect(broker_address)
client.subscribe("gant1/index")
client.subscribe("gant1/majeur")
client.subscribe("gant1/annulaire")
client.subscribe("gant1/auriculaire")
client.loop_forever()