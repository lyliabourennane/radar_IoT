# 🎯 Système de Surveillance Radar IoT avec Alertes Telegram en Temps Réel

> Projet IoT complet : détection d'obstacles par radar, visualisation en temps réel, dashboard Node-RED et alertes intelligentes sur Telegram.

---

## 📋 Description

Ce projet est un système de surveillance radar connecté qui :
- Détecte les obstacles en temps réel avec un capteur ultrasonique
- Visualise le radar graphiquement via Processing
- Transmet les données sur internet via MQTT (HiveMQ Cloud)
- Affiche un dashboard en temps réel avec Node-RED
- Envoie des alertes automatiques sur Telegram classées par niveau de danger 🔴🟠🟡
- Est accessible depuis n'importe où grâce à Ngrok

---

## 🔩 Composants Matériels

| Composant | Rôle |
|-----------|------|
| Arduino Uno | Microcontrôleur principal, contrôle le servo et le capteur |
| Capteur ultrasonique HC-SR04 | Mesure la distance des obstacles (portée 40 cm) |
| Servomoteur SG90 | Fait tourner le capteur de 15° à 165° |
| ESP8266 (NodeMCU) | Module WiFi, envoie les données sur internet via MQTT |
| Buzzer | Signal sonore lors de la détection d'un obstacle |

---

## 💻 Logiciels & Technologies

| Outil | Utilisation |
|-------|-------------|
| Arduino IDE | Programmation de l'Arduino et de l'ESP8266 |
| Processing | Visualisation radar graphique en temps réel |
| Node-RED | Traitement des données + Dashboard web |
| HiveMQ Cloud | Broker MQTT sécurisé (TLS/SSL) |
| Ngrok | Exposition du dashboard sur internet |
| Telegram Bot API | Notifications mobiles automatiques |

---

## 📡 Protocoles Utilisés

- **MQTT** — Communication IoT légère et rapide entre ESP8266 et Node-RED
- **JSON** — Format des données échangées (`{"angle": 90, "dist": 15}`)
- **HTTP GET** — Envoi des alertes vers l'API Telegram
- **TLS/SSL** — Sécurisation de la connexion MQTT (port 8883)

---

## 🗂️ Structure du Projet

```
radar-iot/
│
├── README.md                    ← Ce fichier
│
├── Arduino/
│   └── CODE_Arduino.ino         ← Code radar (servo + capteur + buzzer)
│
├── ESP8266/
│   └── CODE_ESP8266.ino         ← Code WiFi + MQTT
│
├── Processing/
│   └── radar_visualisation.pde  ← Visualisateur radar graphique
│
├── NodeRED/
│   └── flow.json                ← Flow Node-RED complet (import direct)
│
└── Photos/
    ├── montage_hardware.jpg     ← Photo du montage physique
    ├── dashboard.png            ← Capture du dashboard Node-RED
    ├── telegram_alertes.png     ← Capture des alertes Telegram
    └── radar_processing.png     ← Capture du visualisateur Processing
```

---

## ⚙️ Architecture du Système

```
[HC-SR04 + Servo] 
       ↓
  [Arduino Uno]  →(Serial 9600)→  [ESP8266]
                                      ↓
                               [MQTT / HiveMQ Cloud]
                                      ↓
                               [Node-RED]
                              ↙         ↘
                    [Dashboard]     [Telegram Bot]
                    (via Ngrok)    🔴🟠🟡 Alertes
```

---

## 🚀 Installation & Lancement

### 1. Matériel — Branchements Arduino

| Arduino | Composant |
|---------|-----------|
| Pin 10 | HC-SR04 TRIG |
| Pin 11 | HC-SR04 ECHO |
| Pin 12 | Servomoteur signal |
| Pin 2  | Buzzer |
| TX/RX  | ESP8266 RX/TX |

### 2. Code Arduino
- Ouvrir `Arduino/CODE_Arduino.ino` dans Arduino IDE
- Sélectionner la carte **Arduino Uno**
- Téléverser

### 3. Code ESP8266
- **Déconnecter les fils TX/RX** avant de téléverser
- Ouvrir `ESP8266/CODE_ESP8266.ino`
- Modifier le WiFi :
```cpp
const char* ssid     = "VOTRE_WIFI";
const char* password = "VOTRE_MOT_DE_PASSE";
```
- Sélectionner la carte **NodeMCU 1.0 (ESP8266)**
- Téléverser
- **Rebrancher les fils TX/RX** après

### 4. Processing
- Ouvrir `Processing/radar_visualisation.pde`
- Modifier le port série si nécessaire :
```java
myPort = new Serial(this, "COM5", 9600); // Changer COM5 selon votre port
```
- Lancer avec le bouton Play

### 5. Node-RED
```bash
node-red
```
- Aller sur `http://localhost:1880`
- Menu → Import → Coller le contenu de `NodeRED/flow.json`
- Cliquer **Déployer**

### 6. Ngrok (accès depuis internet)
```bash
ngrok http 1880
```
- Copier l'URL générée (ex: `https://xxxx.ngrok-free.app/ui`)

---

## 🤖 Bot Telegram — Niveaux d'Alerte

| Niveau | Distance | Message |
|--------|----------|---------|
| 🔴 DANGER CRITIQUE | < 10 cm | Obstacle très proche |
| 🟠 PROCHE | 10 - 20 cm | Obstacle à distance moyenne |
| 🟡 ATTENTION | 20 - 40 cm | Obstacle détecté |

---

## 📊 Dashboard Node-RED

Le dashboard inclut :
- **Jauge** — Distance en temps réel (0 à 40 cm)
- **Graphe** — Historique de la distance
- **Statut** — OBSTACLE DÉTECTÉ / Libre
- **Compteur** — Nombre total d'obstacles détectés
- **Angle** — Position actuelle du servo
- **Heure** — Dernière détection

---

## 🔐 Configuration HiveMQ Cloud

Le broker MQTT utilisé est **HiveMQ Cloud (Free Tier)** avec connexion sécurisée TLS.

- Host : `xxxxx.s1.eu.hivemq.cloud`
- Port : `8883` (TLS)
- Topic : `radar/data`

---

## 👩‍💻 Auteur

Projet réalisé dans le cadre d'un cours IoT.
