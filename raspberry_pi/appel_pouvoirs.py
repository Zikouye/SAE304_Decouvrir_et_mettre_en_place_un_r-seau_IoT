import mcpi.minecraft as minecraft
import time
import math
import mcpi.block as block
import random

mc = minecraft.Minecraft.create()

# Variable globale pour suivre le dernier temps d'activation des malus
dernier_malus = 0

def envoyer_message(message):
    mc.postToChat(message)

def verifier_temps_malus():
    global dernier_malus
    temps_actuel = time.time()
    if temps_actuel - dernier_malus < 20:
        envoyer_message("Vous devez attendre encore quelques secondes avant de réutiliser un malus.")
        return False
    dernier_malus = temps_actuel
    return True

def malus_index_verre():
    if not verifier_temps_malus():
        return
    player_ids = mc.getPlayerEntityIds()
    if len(player_ids) >= 2:
        player2_pos = mc.entity.getTilePos(player_ids[1])
        x, y, z = player2_pos.x, player2_pos.y, player2_pos.z
        size = 3
        mc.setBlocks(x - size, y, z - size, x + size, y + size * 2, z + size, 20)
        time.sleep(5)
        mc.setBlocks(x - size, y, z - size, x + size, y + size * 2, z + size, 0)
        envoyer_message("Malus appliqué : prison de verre")

def appliquer_malus2():
    if not verifier_temps_malus():
        return
    player_ids = mc.getPlayerEntityIds()
    if len(player_ids) >= 2:
        player2_pos = mc.entity.getTilePos(player_ids[1])
        x, y, z = player2_pos.x, player2_pos.y, player2_pos.z
        size = 3
        mc.setBlocks(x - size, y, z - size, x + size, y + size // 2, z + size, 9)
        time.sleep(5)
        mc.setBlocks(x - size, y, z - size, x + size, y + size // 2, z + size, 0)
        envoyer_message("Malus appliqué : entouré d'eau")

def appliquer_bonus2():
    player_pos = mc.player.getTilePos()
    size = 5
    mc.setBlocks(player_pos.x - size, player_pos.y - 1, player_pos.z - size,
                 player_pos.x + size, player_pos.y - 1, player_pos.z + size,
                 4)
    envoyer_message("Bonus2 appliqué : plateforme de diamants")

def appliquer_malus3():
    if not verifier_temps_malus():
        return
    player_ids = mc.getPlayerEntityIds()
    if len(player_ids) >= 2:
        player2_pos = mc.entity.getTilePos(player_ids[1])
        for _ in range(8):
            dx = random.randint(-5, 5)
            dy = random.randint(-5, 5)
            dz = random.randint(-5, 5)
            x = player2_pos.x + dx
            y = player2_pos.y + dy
            z = player2_pos.z + dz
            mc.setBlock(x, y, z, 0)
        envoyer_message("Malus appliqué : suppression aléatoire de blocs")

def BP_index():
    malus_index_verre()
    time.sleep(0.2)

def BP_majeur():
    appliquer_malus3()

def BP_annulaire():
    appliquer_bonus2()
    time.sleep(0.2)

def BP_auriculaire():
    appliquer_malus2()
    time.sleep(0.2)
