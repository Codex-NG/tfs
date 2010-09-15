NORTH = 0
EAST = 1
SOUTH = 2
WEST = 3
SOUTHWEST = 4
SOUTHEAST = 5
NORTHWEST = 6
NORTHEAST = 7

COMBAT_FORMULA_UNDEFINED = 0
COMBAT_FORMULA_LEVELMAGIC = 1
COMBAT_FORMULA_SKILL = 2
COMBAT_FORMULA_DAMAGE = 3

CONDITION_PARAM_OWNER = 1
CONDITION_PARAM_TICKS = 2
CONDITION_PARAM_OUTFIT = 3
CONDITION_PARAM_HEALTHGAIN = 4
CONDITION_PARAM_HEALTHTICKS = 5
CONDITION_PARAM_MANAGAIN = 6
CONDITION_PARAM_MANATICKS = 7
CONDITION_PARAM_DELAYED = 8
CONDITION_PARAM_SPEED = 9
CONDITION_PARAM_LIGHT_LEVEL = 10
CONDITION_PARAM_LIGHT_COLOR = 11
CONDITION_PARAM_SOULGAIN = 12
CONDITION_PARAM_SOULTICKS = 13
CONDITION_PARAM_MINVALUE = 14
CONDITION_PARAM_MAXVALUE = 15
CONDITION_PARAM_STARTVALUE = 16
CONDITION_PARAM_TICKINTERVAL = 17
CONDITION_PARAM_FORCEUPDATE = 18
CONDITION_PARAM_SKILL_MELEE = 19
CONDITION_PARAM_SKILL_FIST = 20
CONDITION_PARAM_SKILL_CLUB = 21
CONDITION_PARAM_SKILL_SWORD = 22
CONDITION_PARAM_SKILL_AXE = 23
CONDITION_PARAM_SKILL_DISTANCE = 24
CONDITION_PARAM_SKILL_SHIELD = 25
CONDITION_PARAM_SKILL_FISHING = 26
CONDITION_PARAM_STAT_MAXHEALTH = 27
CONDITION_PARAM_STAT_MAXMANA = 28
CONDITION_PARAM_STAT_SOUL = 29
CONDITION_PARAM_STAT_MAGICLEVEL = 30
CONDITION_PARAM_STAT_MAXHEALTHPERCENT = 31
CONDITION_PARAM_STAT_MAXMANAPERCENT = 32
CONDITION_PARAM_STAT_SOULPERCENT = 33
CONDITION_PARAM_STAT_MAGICLEVELPERCENT = 34
CONDITION_PARAM_SKILL_MELEEPERCENT = 35
CONDITION_PARAM_SKILL_FISTPERCENT = 36
CONDITION_PARAM_SKILL_CLUBPERCENT = 37
CONDITION_PARAM_SKILL_SWORDPERCENT = 38
CONDITION_PARAM_SKILL_AXEPERCENT = 39
CONDITION_PARAM_SKILL_DISTANCEPERCENT = 40
CONDITION_PARAM_SKILL_SHIELDPERCENT = 41
CONDITION_PARAM_SKILL_FISHINGPERCENT = 42
CONDITION_PARAM_PERIODICDAMAGE = 43
CONDITION_PARAM_BUFF = 44
CONDITION_PARAM_SUBID = 45
CONDITION_PARAM_FIELD = 46

COMBAT_PARAM_TYPE = 1
COMBAT_PARAM_EFFECT = 2
COMBAT_PARAM_DISTANCEEFFECT = 3
COMBAT_PARAM_BLOCKSHIELD = 4
COMBAT_PARAM_BLOCKARMOR = 5
COMBAT_PARAM_TARGETCASTERORTOPMOST = 6
COMBAT_PARAM_CREATEITEM = 7
COMBAT_PARAM_AGGRESSIVE = 8
COMBAT_PARAM_DISPEL = 9
COMBAT_PARAM_USECHARGES = 10
COMBAT_PARAM_TARGETPLAYERSORSUMMONS = 11
COMBAT_PARAM_DIFFERENTAREADAMAGE = 12
COMBAT_PARAM_HITEFFECT = 13
COMBAT_PARAM_HITCOLOR = 14

CALLBACK_PARAM_LEVELMAGICVALUE = 1
CALLBACK_PARAM_SKILLVALUE = 2
CALLBACK_PARAM_TARGETTILE = 3
CALLBACK_PARAM_TARGETCREATURE = 4

COMBAT_NONE = 0
COMBAT_PHYSICALDAMAGE = 1
COMBAT_ENERGYDAMAGE = 2
COMBAT_EARTHDAMAGE = 4
COMBAT_POISONDAMAGE = 4
COMBAT_FIREDAMAGE = 8
COMBAT_UNDEFINEDDAMAGE = 16
COMBAT_LIFEDRAIN = 32
COMBAT_MANADRAIN = 64
COMBAT_HEALING = 128
COMBAT_DROWNDAMAGE = 256
COMBAT_ICEDAMAGE = 512
COMBAT_HOLYDAMAGE = 1024
COMBAT_DEATHDAMAGE = 2048

CONDITION_NONE = 0
CONDITION_POISON = 1
CONDITION_FIRE = 2
CONDITION_ENERGY = 4
CONDITION_PHYSICAL = 8
CONDITION_HASTE = 16
CONDITION_PARALYZE = 32
CONDITION_OUTFIT = 64
CONDITION_INVISIBLE = 128
CONDITION_LIGHT = 256
CONDITION_MANASHIELD = 512
CONDITION_INFIGHT = 1024
CONDITION_DRUNK = 2048
CONDITION_EXHAUST = 4096
CONDITION_FOOD = 8192
CONDITION_REGENERATION = 8192
CONDITION_SOUL = 16384
CONDITION_DROWN = 32768
CONDITION_MUTED = 65536
CONDITION_ATTRIBUTES = 131072
CONDITION_FREEZING = 262144
CONDITION_DAZZLED = 524288
CONDITION_CURSED = 1048576
CONDITION_PACIFIED = 2097152
CONDITION_GAMEMASTER = 4194304
CONDITION_HUNTING = 8388608

EXHAUST_OTHER = 0
EXHAUST_COMBAT = 1
EXHAUST_HEALING = 2
EXHAUST_WEAPON = 3

MUTED_BUFFER = 0
MUTED_YELL = 1
MUTED_TRADE = 2
MUTED_TRADE_ROOK = 3

GAMEMASTER_INVISIBLE = 0
GAMEMASTER_IGNORE = 1
GAMEMASTER_TELEPORT = 2

CONST_SLOT_FIRST = 1
CONST_SLOT_HEAD = CONST_SLOT_FIRST
CONST_SLOT_NECKLACE = 2
CONST_SLOT_BACKPACK = 3
CONST_SLOT_ARMOR = 4
CONST_SLOT_RIGHT = 5
CONST_SLOT_LEFT = 6
CONST_SLOT_LEGS = 7
CONST_SLOT_FEET = 8
CONST_SLOT_RING = 9
CONST_SLOT_AMMO = 10
CONST_SLOT_LAST = CONST_SLOT_AMMO

CONST_ME_DRAWBLOOD = 0
CONST_ME_LOSEENERGY = 1
CONST_ME_POFF = 2
CONST_ME_BLOCKHIT = 3
CONST_ME_EXPLOSIONAREA = 4
CONST_ME_EXPLOSIONHIT = 5
CONST_ME_FIREAREA = 6
CONST_ME_YELLOW_RINGS = 7
CONST_ME_GREEN_RINGS = 8
CONST_ME_HITAREA = 9
CONST_ME_TELEPORT = 10
CONST_ME_ENERGYHIT = 11
CONST_ME_MAGIC_BLUE = 12
CONST_ME_MAGIC_RED = 13
CONST_ME_MAGIC_GREEN = 14
CONST_ME_HITBYFIRE = 15
CONST_ME_HITBYPOISON = 16
CONST_ME_MORTAREA = 17
CONST_ME_SOUND_GREEN = 18
CONST_ME_SOUND_RED = 19
CONST_ME_POISONAREA = 20
CONST_ME_SOUND_YELLOW = 21
CONST_ME_SOUND_PURPLE = 22
CONST_ME_SOUND_BLUE = 23
CONST_ME_SOUND_WHITE = 24
CONST_ME_BUBBLES = 25
CONST_ME_CRAPS = 26
CONST_ME_GIFT_WRAPS = 27
CONST_ME_FIREWORK_YELLOW = 28
CONST_ME_FIREWORK_RED = 29
CONST_ME_FIREWORK_BLUE = 30
CONST_ME_STUN = 31
CONST_ME_SLEEP = 32
CONST_ME_WATERCREATURE = 33
CONST_ME_GROUNDSHAKER = 34
CONST_ME_HEARTS = 35
CONST_ME_FIREATTACK = 36
CONST_ME_ENERGYAREA = 37
CONST_ME_SMALLCLOUDS = 38
CONST_ME_HOLYDAMAGE = 39
CONST_ME_BIGCLOUDS = 40
CONST_ME_ICEAREA = 41
CONST_ME_ICETORNADO = 42
CONST_ME_ICEATTACK = 43
CONST_ME_STONES = 44
CONST_ME_SMALLPLANTS = 45
CONST_ME_CARNIPHILA = 46
CONST_ME_PURPLEENERGY = 47
CONST_ME_YELLOWENERGY = 48
CONST_ME_HOLYAREA = 49
CONST_ME_BIGPLANTS = 50
CONST_ME_CAKE = 51
CONST_ME_GIANTICE = 52
CONST_ME_WATERSPLASH = 53
CONST_ME_PLANTATTACK = 54
CONST_ME_TUTORIALARROW = 55
CONST_ME_TUTORIALSQUARE = 56
CONST_ME_MIRRORHORIZONTAL = 57
CONST_ME_MIRRORVERTICAL = 58
CONST_ME_SKULLHORIZONTAL = 59
CONST_ME_SKULLVERTICAL = 60
CONST_ME_ASSASSIN = 61
CONST_ME_STEPSHORIZONTAL = 62
CONST_ME_BLOODYSTEPS = 63
CONST_ME_STEPSVERTICAL = 64
CONST_ME_YALAHARIGHOST = 65
CONST_ME_BATS = 66
CONST_ME_SMOKE = 67
CONST_ME_INSECTS = 68
CONST_ME_DRAGONHEAD = 69
CONST_ME_NONE = 255
CONST_ME_LAST = CONST_ME_DRAGONHEAD

CONST_ANI_SPEAR = 0
CONST_ANI_BOLT = 1
CONST_ANI_ARROW = 2
CONST_ANI_FIRE = 3
CONST_ANI_ENERGY = 4
CONST_ANI_POISONARROW = 5
CONST_ANI_BURSTARROW = 6
CONST_ANI_THROWINGSTAR = 7
CONST_ANI_THROWINGKNIFE = 8
CONST_ANI_SMALLSTONE = 9
CONST_ANI_DEATH = 10
CONST_ANI_LARGEROCK = 11
CONST_ANI_SNOWBALL = 12
CONST_ANI_POWERBOLT = 13
CONST_ANI_POISON = 14
CONST_ANI_INFERNALBOLT = 15
CONST_ANI_HUNTINGSPEAR = 16
CONST_ANI_ENCHANTEDSPEAR = 17
CONST_ANI_REDSTAR = 18
CONST_ANI_GREENSTAR = 19
CONST_ANI_ROYALSPEAR = 20
CONST_ANI_SNIPERARROW = 21
CONST_ANI_ONYXARROW = 22
CONST_ANI_PIERCINGBOLT = 23
CONST_ANI_WHIRLWINDSWORD = 24
CONST_ANI_WHIRLWINDAXE = 25
CONST_ANI_WHIRLWINDCLUB = 26
CONST_ANI_ETHEREALSPEAR = 27
CONST_ANI_ICE = 28
CONST_ANI_EARTH = 29
CONST_ANI_HOLY = 30
CONST_ANI_SUDDENDEATH = 31
CONST_ANI_FLASHARROW = 32
CONST_ANI_FLAMMINGARROW = 33
CONST_ANI_SHIVERARROW = 34
CONST_ANI_ENERGYBALL = 35
CONST_ANI_SMALLICE = 36
CONST_ANI_SMALLHOLY = 37
CONST_ANI_SMALLEARTH = 38
CONST_ANI_EARTHARROW = 39
CONST_ANI_EXPLOSION = 40
CONST_ANI_CAKE = 41
CONST_ANI_WEAPONTYPE = 254
CONST_ANI_NONE = 255
CONST_ANI_LAST = CONST_ANI_CAKE

TALKTYPE_FIRST = 1
TALKTYPE_SAY = TALKTYPE_FIRST
TALKTYPE_WHISPER = 2
TALKTYPE_YELL = 3
TALKTYPE_PRIVATE_PN = 4
TALKTYPE_PRIVATE_NP = 5
TALKTYPE_PRIVATE = 6
TALKTYPE_CHANNEL_Y = 7
TALKTYPE_CHANNEL_W = 8
TALKTYPE_BROADCAST = 9
TALKTYPE_MONSTER = 13
TALKTYPE_MONSTER_YELL = 14
TALKTYPE_LAST = TALKTYPE_MONSTER_YELL

-- TODO: Find what can we do with those
TALKTYPE_UNKNOWN_1 = 10
TALKTYPE_UNKNOWN_2 = 11
TALKTYPE_UNKNOWN_3 = 12

-- Keept for compatibility, no more use
TALKTYPE_RVR_CHANNEL = 255 + 1
TALKTYPE_RVR_ANSWER = 255 + 2
TALKTYPE_RVR_CONTINUE = 255 + 3

-- Keept for compatibility
TALKTYPE_CHANNEL_O = TALKTYPE_CHANNEL_Y
TALKTYPE_CHANNEL_RN = TALKTYPE_CHANNEL_Y
TALKTYPE_CHANNEL_RA = TALKTYPE_CHANNEL_W
TALKTYPE_PRIVATE_RED = TALKTYPE_PRIVATE

TALKTYPE_TYPES = {
	["say"] = TALKTYPE_SAY,
	["whisper"] = TALKTYPE_WHISPER,
	["yell"] = TALKTYPE_YELL,
	["private-playernpc"] = TALKTYPE_PRIVATE_PN,
	["private-npcplayer"] = TALKTYPE_PRIVATE_NP,
	["private"] = TALKTYPE_PRIVATE,
	["channel-yellow"] = TALKTYPE_CHANNEL_Y,
	["channel-white"] = TALKTYPE_CHANNEL_W,
	["broadcast"] = TALKTYPE_BROADCAST,
	["monster"] = TALKTYPE_MONSTER,
	["monster-yell"] = TALKTYPE_MONSTER_YELL,

	["rvr-channel"] = TALKTYPE_RVR_CHANNEL,
	["rvr-answer"] = TALKTYPE_RVR_ANSWER,
	["rvr-continue"] = TALKTYPE_RVR_CONTINUE,
	["channel-orange"] = TALKTYPE_CHANNEL_O,
	["channel-red"] = TALKTYPE_CHANNEL_RN,
	["channel-redanonymous"] = TALKTYPE_CHANNEL_RA,
	["private-red"] = TALKTYPE_PRIVATE_RED
}

MESSAGE_FIRST = 12
MESSAGE_STATUS_CONSOLE_RED = MESSAGE_FIRST
MESSAGE_EVENT_ORANGE = 13
MESSAGE_STATUS_CONSOLE_ORANGE = 14
MESSAGE_STATUS_WARNING = 15
MESSAGE_EVENT_ADVANCE = 16
MESSAGE_EVENT_DEFAULT = 17
MESSAGE_STATUS_DEFAULT = 18
MESSAGE_INFO_DESCR = 19
MESSAGE_STATUS_SMALL = 20
MESSAGE_STATUS_CONSOLE_BLUE = 21
MESSAGE_LAST = MESSAGE_STATUS_CONSOLE_BLUE

MESSAGE_TYPES = {
	["advance"] = MESSAGE_EVENT_ADVANCE,
	["event"] = MESSAGE_EVENT_DEFAULT,
	["white"] = MESSAGE_EVENT_DEFAULT,
	["orange"] = MESSAGE_STATUS_CONSOLE_ORANGE,
	["info"] = MESSAGE_INFO_DESCR,
	["green"] = MESSAGE_INFO_DESCR,
	["small"] = MESSAGE_STATUS_SMALL,
	["blue"] = MESSAGE_STATUS_CONSOLE_BLUE,
	["red"] = MESSAGE_STATUS_CONSOLE_RED,
	["warning"] = MESSAGE_STATUS_WARNING,
	["status"] = MESSAGE_STATUS_DEFAULT
}

COLOR_BLACK = 0
COLOR_BLUE = 5
COLOR_GREEN = 18
COLOR_LIGHTGREEN = 66
COLOR_DARKBROWN = 78
COLOR_LIGHTBLUE = 89
COLOR_DARKRED = 108
COLOR_DARKPURPLE = 112
COLOR_BROWN = 120
COLOR_GREY = 129
COLOR_TEAL = 143
COLOR_DARKPINK = 152
COLOR_PURPLE = 154
COLOR_DARKORANGE = 156
COLOR_RED = 180
COLOR_PINK = 190
COLOR_ORANGE = 192
COLOR_DARKYELLOW = 205
COLOR_YELLOW = 210
COLOR_WHITE = 215
COLOR_NONE = 255

MAPMARK_TICK = 0
MAPMARK_QUESTION = 1
MAPMARK_EXCLAMATION = 2
MAPMARK_STAR = 3
MAPMARK_CROSS = 4
MAPMARK_TEMPLE = 5
MAPMARK_KISS = 6
MAPMARK_SHOVEL = 7
MAPMARK_SWORD = 8
MAPMARK_FLAG = 9
MAPMARK_LOCK = 10
MAPMARK_BAG = 11
MAPMARK_SKULL = 12
MAPMARK_DOLLAR = 13
MAPMARK_REDNORTH = 14
MAPMARK_REDSOUTH = 15
MAPMARK_REDEAST = 16
MAPMARK_REDWEST = 17
MAPMARK_GREENNORTH = 18
MAPMARK_GREENSOUTH = 19

ITEM_TYPE_NONE = 0
ITEM_TYPE_DEPOT = 1
ITEM_TYPE_MAILBOX = 2
ITEM_TYPE_TRASHHOLDER = 3
ITEM_TYPE_CONTAINER = 4
ITEM_TYPE_DOOR = 5
ITEM_TYPE_MAGICFIELD = 6
ITEM_TYPE_TELEPORT = 7
ITEM_TYPE_BED = 8
ITEM_TYPE_KEY = 9
ITEM_TYPE_RUNE = 10

ITEM_GROUP_NONE = 0
ITEM_GROUP_GROUND = 1
ITEM_GROUP_CONTAINER = 2
ITEM_GROUP_CHARGES = 6
ITEM_GROUP_SPLASH = 11
ITEM_GROUP_FLUID = 12

CONST_PROP_BLOCKSOLID = 0
CONST_PROP_HASHEIGHT = 1
CONST_PROP_BLOCKPROJECTILE = 2
CONST_PROP_BLOCKPATHFIND = 3
CONST_PROP_ISVERTICAL = 4
CONST_PROP_ISHORIZONTAL = 5
CONST_PROP_MOVABLE = 6
CONST_PROP_BLOCKINGANDNOTMOVABLE = 7
CONST_PROP_SUPPORTHANGABLE = 8

CHASEMODE_STANDSTILL = 0
CHASEMODE_FOLLOW = 1

FIGHTMODE_ATTACK = 0
FIGHTMODE_BALANCED = 1
FIGHTMODE_DEFENSE = 2

SECUREMODE_ON = 0
SECUREMODE_OFF = 1

TRADE_NONE = 0
TRADE_INITIATED = 1
TRADE_ACCEPT = 2
TRADE_ACKNOWLEDGE = 3
TRADE_TRANSFER = 4

MANAGER_NONE = 0
MANAGER_NEW = 1
MANAGER_ACCOUNT = 2
MANAGER_NAMELOCK = 3

PLAYERSEX_FEMALE = 0
PLAYERSEX_MALE = 1
PLAYERSEX_GAMEMASTER = 2

PLAYERLOSS_EXPERIENCE = 0
PLAYERLOSS_MANA = 1
PLAYERLOSS_SKILLS = 2
PLAYERLOSS_CONTAINERS = 3
PLAYERLOSS_ITEMS = 4

STATSCHANGE_HEALTHGAIN = 0
STATSCHANGE_HEALTHLOSS = 1
STATSCHANGE_MANAGAIN = 2
STATSCHANGE_MANALOSS = 3

SKILL_FIRST = 0
SKILL_FIST = SKILL_FIRST
SKILL_CLUB = 1
SKILL_SWORD = 2
SKILL_AXE = 3
SKILL_DISTANCE = 4
SKILL_SHIELD = 5
SKILL_FISHING = 6
SKILL__MAGLEVEL = 7
SKILL__LEVEL = 8
SKILL_LAST = SKILL_FISHING
SKILL__LAST = SKILL__LEVEL

SKILL_NAMES = {
	[SKILL_FIST] = "fist fighting",
	[SKILL_CLUB] = "club fighting",
	[SKILL_SWORD] = "sword fighting",
	[SKILL_AXE] = "axe fighting",
	[SKILL_DISTANCE] = "distance fighting",
	[SKILL_SHIELD] = "shielding",
	[SKILL_FISHING] = "fishing",
	[SKILL__LEVEL] = "level",
	[SKILL__MAGLEVEL] = "magic level"
}

SKILL_IDS = {
	["fist"] = SKILL_FIST,
	["club"] = SKILL_CLUB,
	["sword"] = SKILL_SWORD,
	["axe"] = SKILL_AXE,
	["distance"] = SKILL_DISTANCE,
	["dist"] = SKILL_DISTANCE,
	["shielding"] = SKILL_SHIELD,
	["shield"] = SKILL_SHIELD,
	["fishing"] = SKILL_FISHING,
	["fish"] = SKILL_FISHING,
	["level"] = SKILL__LEVEL,
	["magic"] = SKILL__MAGLEVEL
}

GUILD_MEMBER = 1
GUILD_VICE = 2
GUILD_LEADER = 3

SKULL_NONE = 0
SKULL_YELLOW = 1
SKULL_GREEN = 2
SKULL_WHITE = 3
SKULL_RED = 4
SKULL_BLACK = 5
SKULL_LAST = SKULL_BLACK

SHIELD_NONE = 0
SHIELD_WHITEYELLOW = 1
SHIELD_WHITEBLUE = 2
SHIELD_BLUE = 3
SHIELD_YELLOW = 4
SHIELD_BLUE_SHAREDEXP = 5
SHIELD_YELLOW_SHAREDEXP = 6
SHIELD_BLUE_NOSHAREDEXP_BLINK = 7
SHIELD_YELLOW_NOSHAREDEXP_BLINK = 8
SHIELD_BLUE_NOSHAREDEXP = 9
SHIELD_YELLOW_NOSHAREDEXP = 10
SHIELD_LAST = SHIELD_YELLOW_NOSHAREDEXP

EMBLEM_NONE = 0
EMBLEM_GREEN = 1
EMBLEM_RED = 2
EMBLEM_BLUE = 3

WORLDTYPE_OPTIONAL = 1
WORLDTYPE_OPEN = 2
WORLDTYPE_HARDCORE = 3

DATABASE_NONE = 0
DATABASE_MYSQL = 1
DATABASE_SQLITE = 2
DATABASE_POSTGRESQL = 3
DATABASE_ODBC = 4

GAMESTATE_STARTUP = 1
GAMESTATE_INIT = 2
GAMESTATE_NORMAL = 3
GAMESTATE_MAINTAIN = 4
GAMESTATE_CLOSED = 5
GAMESTATE_CLOSING = 6
GAMESTATE_SHUTDOWN = 7

RELOAD_ACTIONS = 1
RELOAD_CHAT = 2
RELOAD_CONFIG = 3
RELOAD_CREATUREEVENTS = 4
RELOAD_GAMESERVERS = 5
RELOAD_GLOBALEVENTS = 6
RELOAD_GROUPS = 7
RELOAD_HIGHSCORES = 8
RELOAD_HOUSEPRICES = 9
RELOAD_ITEMS = 10
RELOAD_MONSTERS = 11
RELOAD_MOVEEVENTS = 12
RELOAD_NPCS = 13
RELOAD_OUTFITS = 14
RELOAD_QUESTS = 15
RELOAD_RAIDS = 16
RELOAD_SPELLS = 17
RELOAD_STAGES = 18
RELOAD_TALKACTIONS = 19
RELOAD_VOCATIONS = 20
RELOAD_WEAPONS = 21
RELOAD_MODS = 22
RELOAD_ALL = 23

BAN_NONE = 0
BAN_IP = 1
BAN_PLAYER = 2
BAN_ACCOUNT = 3
BAN_NOTATION = 4
BAN_STATEMENT = 5

PLAYERBAN_NONE = 0
PLAYERBAN_REPORT = 1
PLAYERBAN_LOCK = 2
PLAYERBAN_BANISHMENT = 3

CHANNEL_GUILD = 0
CHANNEL_PARTY = 1
CHANNEL_RVR = 3
CHANNEL_HELP = 9
CHANNEL_DEFAULT = 0xFFFE
CHANNEL_PRIVATE = 0xFFFF

STACKPOS_GROUND = 0
STACKPOS_TOP_CREATURE = 253
STACKPOS_TOP_FIELD = 254
STACKPOS_TOP_MOVABLE_ITEM_OR_CREATURE = 255

WEAPON_NONE = 0
WEAPON_SWORD = 1
WEAPON_CLUB = 2
WEAPON_AXE = 3
WEAPON_DIST = 4
WEAPON_SHIELD = 5
WEAPON_FIST = 6
WEAPON_WAND = 7
WEAPON_AMMO = 8

ACTION_NOTATION = 0
ACTION_NAMEREPORT = 1
ACTION_BANISHMENT = 2
ACTION_BANREPORT = 3
ACTION_BANFINAL = 4
ACTION_BANREPORTFINAL = 5
ACTION_STATEMENT = 6
ACTION_DELETION = 7
ACTION_NAMELOCK = 8
ACTION_BANLOCK = 9
ACTION_BANLOCKFINAL = 10
ACTION_PLACEHOLDER = 11

RECURSE_NONE = 0
RECURSE_FIRST = 1
RECURSE_ALL = 2

ITEM_GOLD_COIN = 2148
ITEM_PLATINUM_COIN = 2152
ITEM_CRYSTAL_COIN = 2160
ITEM_SCARAB_COIN = 2159
ITEM_FISH = 2667
ITEM_WORM = 3976
ITEM_MECHANICAL_FISH = 10224
ITEM_NAIL = 8309
ITEM_MECHANICAL_FISHING_ROD = 10223
ITEM_GREEN_PERCH = 7159
ITEM_RAINBOW_TROUT = 7158
ITEM_NORTHERN_PIKE = 2669
ITEM_PARCEL = 2595
ITEM_LABEL = 2599

RETURNVALUE_DONTSHOWMESSAGE = 0
RETURNVALUE_NOERROR = 1
RETURNVALUE_NOTPOSSIBLE = 2
RETURNVALUE_NOTENOUGHROOM = 3
RETURNVALUE_PLAYERISPZLOCKED = 4
RETURNVALUE_PLAYERISNOTINVITED = 5
RETURNVALUE_CANNOTTHROW = 6
RETURNVALUE_THEREISNOWAY = 7
RETURNVALUE_DESTINATIONOUTOFREACH = 8
RETURNVALUE_CREATUREBLOCK = 9
RETURNVALUE_NOTMOVABLE = 10
RETURNVALUE_DROPTWOHANDEDITEM = 11
RETURNVALUE_BOTHHANDSNEEDTOBEFREE = 12
RETURNVALUE_CANONLYUSEONEWEAPON = 13
RETURNVALUE_NEEDEXCHANGE = 14
RETURNVALUE_CANNOTBEDRESSED = 15
RETURNVALUE_PUTTHISOBJECTINYOURHAND = 16
RETURNVALUE_PUTTHISOBJECTINBOTHHANDS = 17
RETURNVALUE_TOOFARAWAY = 18
RETURNVALUE_FIRSTGODOWNSTAIRS = 19
RETURNVALUE_FIRSTGOUPSTAIRS = 20
RETURNVALUE_CONTAINERNOTENOUGHROOM = 21
RETURNVALUE_NOTENOUGHCAPACITY = 22
RETURNVALUE_CANNOTPICKUP = 23
RETURNVALUE_THISISIMPOSSIBLE = 24
RETURNVALUE_DEPOTISFULL = 25
RETURNVALUE_CREATUREDOESNOTEXIST = 26
RETURNVALUE_CANNOTUSETHISOBJECT = 27
RETURNVALUE_PLAYERWITHTHISNAMEISNOTONLINE = 28
RETURNVALUE_NOTREQUIREDLEVELTOUSERUNE = 29
RETURNVALUE_YOUAREALREADYTRADING = 30
RETURNVALUE_THISPLAYERISALREADYTRADING = 31
RETURNVALUE_YOUMAYNOTLOGOUTDURINGAFIGHT = 32
RETURNVALUE_DIRECTPLAYERSHOOT = 33
RETURNVALUE_NOTENOUGHLEVEL = 34
RETURNVALUE_NOTENOUGHMAGICLEVEL = 35
RETURNVALUE_NOTENOUGHMANA = 36
RETURNVALUE_NOTENOUGHSOUL = 37
RETURNVALUE_YOUAREEXHAUSTED = 38
RETURNVALUE_PLAYERISNOTREACHABLE = 39
RETURNVALUE_CANONLYUSETHISRUNEONCREATURES = 40
RETURNVALUE_ACTIONNOTPERMITTEDINPROTECTIONZONE = 41
RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER = 42
RETURNVALUE_YOUMAYNOTATTACKAPERSONINPROTECTIONZONE = 43
RETURNVALUE_YOUMAYNOTATTACKAPERSONWHILEINPROTECTIONZONE = 44
RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE = 45
RETURNVALUE_YOUCANONLYUSEITONCREATURES = 46
RETURNVALUE_CREATUREISNOTREACHABLE = 47
RETURNVALUE_TURNSECUREMODETOATTACKUNMARKEDPLAYERS = 48
RETURNVALUE_YOUNEEDPREMIUMACCOUNT = 49
RETURNVALUE_YOUNEEDTOLEARNTHISSPELL = 50
RETURNVALUE_YOURVOCATIONCANNOTUSETHISSPELL = 51
RETURNVALUE_YOUNEEDAWEAPONTOUSETHISSPELL = 52
RETURNVALUE_PLAYERISPZLOCKEDLEAVEPVPZONE = 53
RETURNVALUE_PLAYERISPZLOCKEDENTERPVPZONE = 54
RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE = 55
RETURNVALUE_YOUCANNOTLOGOUTHERE = 56
RETURNVALUE_YOUNEEDAMAGICITEMTOCASTSPELL = 57
RETURNVALUE_CANNOTCONJUREITEMHERE = 58
RETURNVALUE_TILEISFULL = 59
RETURNVALUE_NAMEISTOOAMBIGUOUS = 60
RETURNVALUE_CANONLYUSEONESHIELD = 61
RETURNVALUE_YOUARENOTTHEOWNER = 62
RETURNVALUE_YOUMAYNOTCASTAREAONBLACKSKULL = 63

CONTAINER_POSITION = 0xFFFF
EMPTY_STORAGE = -1
EMPTY_RESULT = -1
ITEMCOUNT_MAX = 100

AUTOID_PLAYERS = 0x10000000
AUTOID_MONSTERS = 0x40000000
AUTOID_NPCS = 0x80000000

PLAYERFLAG_CANNOTUSECOMBAT = 0
PLAYERFLAG_CANNOTATTACKPLAYER = 1
PLAYERFLAG_CANNOTATTACKMONSTER = 2
PLAYERFLAG_CANNOTBEATTACKED = 3
PLAYERFLAG_CANCONVINCEALL = 4
PLAYERFLAG_CANSUMMONALL = 5
PLAYERFLAG_CANILLUSIONALL = 6
PLAYERFLAG_CANSENSEINVISIBILITY = 7
PLAYERFLAG_IGNOREDBYMONSTERS = 8
PLAYERFLAG_NOTGAININFIGHT = 9
PLAYERFLAG_HASINFINITEMANA = 10
PLAYERFLAG_HASINFINITESOUL = 11
PLAYERFLAG_HASNOEXHAUSTION = 12
PLAYERFLAG_CANNOTUSESPELLS = 13
PLAYERFLAG_CANNOTPICKUPITEM = 14
PLAYERFLAG_CANALWAYSLOGIN = 15
PLAYERFLAG_CANBROADCAST = 16
PLAYERFLAG_CANEDITHOUSES = 17
PLAYERFLAG_CANNOTBEBANNED = 18
PLAYERFLAG_CANNOTBEPUSHED = 19
PLAYERFLAG_HASINFINITECAPACITY = 20
PLAYERFLAG_CANPUSHALLCREATURES = 21
PLAYERFLAG_CANTALKREDPRIVATE = 22
PLAYERFLAG_CANTALKREDCHANNEL = 23
PLAYERFLAG_TALKORANGEHELPCHANNEL = 24
PLAYERFLAG_NOTGAINEXPERIENCE = 25
PLAYERFLAG_NOTGAINMANA = 26
PLAYERFLAG_NOTGAINHEALTH = 27
PLAYERFLAG_NOTGAINSKILL = 28
PLAYERFLAG_SETMAXSPEED = 29
PLAYERFLAG_SPECIALVIP = 30
PLAYERFLAG_NOTGENERATELOOT = 31
PLAYERFLAG_CANTALKREDCHANNELANONYMOUS = 32
PLAYERFLAG_IGNOREPROTECTIONZONE = 33
PLAYERFLAG_IGNORESPELLCHECK = 34
PLAYERFLAG_IGNOREWEAPONCHECK = 35
PLAYERFLAG_CANNOTBEMUTED = 36
PLAYERFLAG_ISALWAYSPREMIUM = 37
PLAYERFLAG_CANANSWERRULEVIOLATIONS = 38
PLAYERFLAG_39 = 39 -- ignore
PLAYERFLAG_SHOWGROUPINSTEADOFVOCATION = 40
PLAYERFLAG_HASINFINITESTAMINA = 41
PLAYERFLAG_CANNOTMOVEITEMS = 42
PLAYERFLAG_CANNOTMOVECREATURES = 43
PLAYERFLAG_CANREPORTBUGS = 44
PLAYERFLAG_45 = 45 -- ignore
PLAYERFLAG_CANNOTBESEEN = 46
PLAYERFLAG_HIDEHEALTH = 47

PLAYERCUSTOMFLAG_ALLOWIDLE = 0
PLAYERCUSTOMFLAG_CANSEEPOSITION	= 1
PLAYERCUSTOMFLAG_CANSEEITEMDETAILS = 2
PLAYERCUSTOMFLAG_CANSEECREATUREDETAILS = 3
PLAYERCUSTOMFLAG_NOTSEARCHABLE = 4
PLAYERCUSTOMFLAG_GAMEMASTERPRIVILEGES = 5
PLAYERCUSTOMFLAG_CANTHROWANYWHERE = 6
PLAYERCUSTOMFLAG_CANPUSHALLITEMS = 7
PLAYERCUSTOMFLAG_CANMOVEANYWHERE = 8
PLAYERCUSTOMFLAG_CANMOVEFROMFAR = 9
PLAYERCUSTOMFLAG_CANLOGINMULTIPLECHARACTERS = 10
PLAYERCUSTOMFLAG_HASFULLLIGHT = 11
PLAYERCUSTOMFLAG_CANLOGOUTANYTIME = 12
PLAYERCUSTOMFLAG_HIDELEVEL = 13
PLAYERCUSTOMFLAG_ISPROTECTED = 14
PLAYERCUSTOMFLAG_ISIMMUNE = 15
PLAYERCUSTOMFLAG_NOTGAINSKULL = 16
PLAYERCUSTOMFLAG_NOTGAINUNJUSTIFIED = 17
PLAYERCUSTOMFLAG_IGNOREPACIFICATION = 18
PLAYERCUSTOMFLAG_IGNORELOGINDELAY = 19
PLAYERCUSTOMFLAG_CANSTAIRHOP = 20
PLAYERCUSTOMFLAG_CANTURNHOP = 21
PLAYERCUSTOMFLAG_IGNOREHOUSERENT = 22
PLAYERCUSTOMFLAG_CANWEARALLADDONS = 23
PLAYERCUSTOMFLAG_ISWALKABLE = 24
PLAYERCUSTOMFLAG_CANWALKTHROUGH = 25

maleOutfits = {128, 129, 130, 131, 132, 133, 134, 143, 144, 145, 146, 151, 152, 153, 154, 251, 268, 273, 278, 289, 325, 328, 335, 367}
femaleOutfits = {136, 137, 138, 139, 140, 141, 142, 147, 148, 149, 150, 155, 156, 157, 158, 252, 269, 270, 279, 288, 324, 329, 336, 366}

doors = {[1209] = 1211, [1210] = 1211, [1212] = 1214, [1213] = 1214, [1219] = 1220, [1221] = 1222, [1231] = 1233, [1232] = 1233, [1234] = 1236, [1235] = 1236, [1237] = 1238, [1239] = 1240, [1249] = 1251, [1250] = 1251, [1252] = 1254, [1253] = 1254, [1539] = 1540, [1541] = 1542, [3535] = 3537, [3536] = 3537, [3538] = 3539, [3544] = 3546, [3545] = 3546, [3547] = 3548, [4913] = 4915, [4914] = 4915, [4916] = 4918, [4917] = 4918, [5082] = 5083, [5084] = 5085, [5098] = 5100, [5099] = 5100, [5101] = 5102, [5107] = 5109, [5108] = 5109, [5110] = 5111, [5116] = 5118, [5117] = 5118, [5119] = 5120, [5125] = 5127, [5126] = 5127, [5128] = 5129, [5134] = 5136, [5135] = 5136, [5137] = 5139, [5138] = 5139, [5140] = 5142, [5141] = 5142, [5143] = 5145, [5144] = 5145, [5278] = 5280, [5279] = 5280, [5281] = 5283, [5282] = 5283, [5284] = 5285, [5286] = 5287, [5515] = 5516, [5517] = 5518, [5732] = 5734, [5733] = 5734, [5735] = 5737, [5736] = 5737, [6192] = 6194, [6193] = 6194, [6195] = 6197, [6196] = 6197, [6198] = 6199, [6200] = 6201, [6249] = 6251, [6250] = 6251, [6252] = 6254, [6253] = 6254, [6255] = 6256, [6257] = 6258, [6795] = 6796, [6797] = 6798, [6799] = 6800, [6801] = 6802, [6891] = 6893, [6892] = 6893, [6894] = 6895, [6900] = 6902, [6901] = 6902, [6903] = 6904, [7033] = 7035, [7034] = 7035, [7036] = 7037, [7042] = 7044, [7043] = 7044, [7045] = 7046, [7054] = 7055, [7056] = 7057, [8541] = 8543, [8542] = 8543, [8544] = 8546, [8545] = 8546, [8547] = 8548, [8549] = 8550, [9165] = 9167, [9166] = 9167, [9168] = 9170, [9169] = 9170, [9171] = 9172, [9173] = 9174, [9267] = 9269, [9268] = 9269, [9270] = 9272, [9271] = 9272, [9273] = 9274, [9275] = 9276, [10276] = 10277, [10274] = 10275, [10268] = 10270, [10269] = 10270, [10271] = 10273, [10272] = 10273, [10471] = 10472, [10480] = 10481, [10477] = 10479, [10478] = 10479, [10468] = 10470, [10469] = 10470, [10775] = 10777, [10776] = 10777, [10780] = 10781, [10782] = 10783, [10784] = 10786, [10785] = 10786, [10789] = 10790, [10791] = 10792}
closingDoors = {1224, 1226, 1228, 1230, 1242, 1244, 1246, 1248, 1256, 1258, 1260, 1262, 3541, 3543, 3550, 3552, 5104, 5106, 5113, 5115, 5122, 5124, 5131, 5133, 5289, 5291, 5293, 5295, 6203, 6205, 6207, 6209, 6260, 6262, 6264, 6266, 6897, 6899, 6906, 6908, 7039, 7041, 7048, 7050, 8552, 8554, 8556, 8558, 9176, 9178, 9180, 9182, 9278, 9280, 9282, 9284, 10279, 10281, 10283, 10285, 10474, 10476, 10483, 10485, 10781, 10783, 10790, 10792}
verticalOpenDoors = {1211, 1220, 1224, 1228, 1233, 1238, 1242, 1246, 1251, 1256, 1260, 1540, 3546, 3548, 3550, 3552, 4915, 5083, 5109, 5111, 5113, 5115, 5127, 5129, 5131, 5133, 5142, 5145, 5283, 5285, 5289, 5293, 5516, 5737, 5749, 6194, 6199, 6203, 6207, 6251, 6256, 6260, 6264, 6798, 6802, 6902, 6904, 6906, 6908, 7044, 7046, 7048, 7050, 7055, 8543, 8548, 8552, 8556, 9167, 9172, 9269, 9274, 9278, 9282, 10270, 10275, 10279, 10283, 10479, 10481, 10483, 10485, 10790, 10792}
horizontalOpenDoors = {1214, 1222, 1226, 1230, 1236, 1240, 1244, 1248, 1254, 1258, 1262, 1542, 3537, 3539, 3541, 3543, 4918, 5085, 5100, 5102, 5104, 5106, 5118, 5120, 5122, 5124, 5136, 5139, 5280, 5287, 5291, 5295, 5518, 5734, 5746, 6197, 6201, 6205, 6209, 6254, 6258, 6262, 6266, 6796, 6800, 6893, 6895, 6897, 6899, 7035, 7037, 7039, 7041, 7057, 8546, 8550, 8554, 8558, 9170, 9174, 9272, 9276, 9280, 9284, 10273, 10277, 10281, 10285, 10470, 10472, 10474, 10476, 10781, 10783}
specialDoors = {1223, 1225, 1241, 1243, 1255, 1257, 3542, 3551, 5105, 5114, 5123, 5132, 5288, 5290, 5745, 5748, 6202, 6204, 6259, 6261, 6898, 6907, 7040, 7049, 8551, 8553, 9175, 9177, 9277, 9279, 10278, 10280, 10475, 10484, 10782, 10791}
keys = {2086, 2087, 2088, 2089, 2090, 2091, 2092, 10032, 10091}

enchantableGems = {2147, 2146, 2149, 2150}
enchantableItems = {2383, 7383, 7384, 7406, 7402, 2429, 2430, 7389, 7380, 2454, 2423, 2445, 7415, 7392, 2391, 2544, 8905}
enchantingAltars = {
	{7504, 7505, 7506, 7507},
	{7508, 7509, 7510, 7511},
	{7516, 7517, 7518, 7519},
	{7512, 7513, 7514, 7515}
}
enchantedGems = {7760, 7759, 7761, 7762}
enchantedItems = {
	[2383] = {7744, 7763, 7854, 7869},
	[7383] = {7745, 7764, 7855, 7870},
	[7384] = {7746, 7765, 7856, 7871},
	[7406] = {7747, 7766, 7857, 7872},
	[7402] = {7748, 7767, 7858, 7873},
	[2429] = {7749, 7768, 7859, 7874},
	[2430] = {7750, 7769, 7860, 7875},
	[7389] = {7751, 7770, 7861, 7876},
	[7380] = {7752, 7771, 7862, 7877},
	[2454] = {7753, 7772, 7863, 7878},
	[2423] = {7754, 7773, 7864, 7879},
	[2445] = {7755, 7774, 7865, 7880},
	[7415] = {7756, 7775, 7866, 7881},
	[7392] = {7757, 7776, 7867, 7882},
	[2391] = {7758, 7777, 7868, 7883},
	[2544] = {7840, 7839, 7850, 7838},
	[8905] = {8906, 8907, 8909, 8908}
}

Config_meta =
{
	__index = function(t, k)
		if(k == "type") then
			return function()
				return "Config"
			end
		end

		return getConfigValue(k)
	end,

	__newindex = function(t, k, v)
		return false
	end
}

CONFIG = {}
setmetatable(CONFIG, Config_meta)

Storage_meta =
{
	__index = function(t, k)
		if(k == "type") then
			return function()
				return "Storage"
			end
		end

		return getStorage(k)
	end,

	__newindex = function(t, k, v)
		return doSetStorage(k, v)
	end
}

STORAGE = {}
setmetatable(STORAGE, Storage_meta)
