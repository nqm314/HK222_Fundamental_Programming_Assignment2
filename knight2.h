#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

bool isPrime(int HP);
bool isPaladin(int HP);
bool isLancelot(int HP);
bool isDragonKnight(int HP);
bool isNormalKnight(int HP);

class Events;
class BaseItem;
class BaseBag;
class BaseKnight;
class ArmyKnights;
class BaseOpponent;
class KnightAdventure;
class PaladinBag;
class DragonBag;
class LancelotBag;
class NormalBag;

enum ItemType {
  ANTIDOTE = 0,
  PHOENIXDOWNI,
  PHOENIXDOWNII,
  PHOENIXDOWNIII,
  PHOENIXDOWNIV
};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };

class Events {
private:
  int numEvents;
  int *eventsID;

public:
  Events(const string &file_events) {
    ifstream events(file_events);
    string line;
    events >> numEvents;
    getline(events, line);
    eventsID = new int[numEvents];
    for (int i = 0; i < numEvents; i++) {
      events >> eventsID[i];
    }
  }
  int count() const { return numEvents; }
  int get(int i) const { return eventsID[i]; }
  ~Events() { delete[] eventsID; }
};

class BaseOpponent {
protected:
  int levelO;

public:
  virtual int geteventID() = 0;
  void setLevelO(int level) { this->levelO = level; };
  int LevelO() { return levelO; };
  ~BaseOpponent(){};
};

class MadBear : public BaseOpponent {
public:
  int geteventID() override { return 1; }
};
class Bandit : public BaseOpponent {
public:
  int geteventID() override { return 2; }
};
class LordLupin : public BaseOpponent {
public:
  int geteventID() override { return 3; }
};
class Elf : public BaseOpponent {
public:
  int geteventID() override { return 4; }
};
class Troll : public BaseOpponent {
public:
  int geteventID() override { return 5; }
};
class Tornbery : public BaseOpponent {
public:
  int geteventID() override { return 6; }
};
class QueenOfCards : public BaseOpponent {
public:
  int geteventID() override { return 7; }
};
class NinaDeRings : public BaseOpponent {
public:
  int geteventID() override { return 8; }
};
class DurianGarden : public BaseOpponent {
public:
  int geteventID() override { return 9; }
};
class OmegaWeapon : public BaseOpponent {
public:
  int geteventID() override { return 10; }
};
class Hades : public BaseOpponent {
public:
  int geteventID() override { return 11; }
};

class BaseItem {
protected:
  ItemType itemtype;

public:
  virtual ItemType getItemType() { return itemtype; };
  virtual string getTypeString() = 0;
  virtual bool canUse(BaseKnight *knight) = 0;
  virtual void use(BaseKnight *knight) = 0;
  virtual ~BaseItem(){};
};

class Antidote : public BaseItem {
private:
  int numAntidote = 0;

public:
  Antidote();
  ~Antidote(){};
  int getnumAntidote();
  string getTypeString() override { return "Antidote"; }
  bool canUse(BaseKnight *knight) override { return true; }
  void use(BaseKnight *knight) override{};
};

class PhoenixDownI : public BaseItem {
private:
  int numPhoenixDownI = 0;

public:
  PhoenixDownI();
  ~PhoenixDownI(){};
  int getnumPhoenixDownI() { return this->numPhoenixDownI; }
  string getTypeString() override { return "PhoenixI"; }
  bool canUse(BaseKnight *knight) override;
  void use(BaseKnight *knight) override;
};

class PhoenixDownII : public BaseItem {
private:
  int numPhoenixDownII = 0;

public:
  PhoenixDownII();
  ~PhoenixDownII(){};
  int getnumPhoenixDownII() { return this->numPhoenixDownII; }
  string getTypeString() override { return "PhoenixII"; }
  bool canUse(BaseKnight *knight) override;
  void use(BaseKnight *knight) override;
};

class PhoenixDownIII : public BaseItem {
private:
  int numPhoenixDownIII = 0;

public:
  PhoenixDownIII();
  ~PhoenixDownIII(){};
  int getnumPhoenixDownIII() { return this->numPhoenixDownIII; }
  string getTypeString() override { return "PhoenixIII"; }
  bool canUse(BaseKnight *knight) override;
  void use(BaseKnight *knight) override;
};

class PhoenixDownIV : public BaseItem {
private:
  int numPhoenixDownIV = 0;

public:
  PhoenixDownIV();
  ~PhoenixDownIV(){};
  int getnumPhoenixDownIV() { return this->numPhoenixDownIV; }
  string getTypeString() override { return "PhoenixIV"; }
  bool canUse(BaseKnight *knight) override;
  void use(BaseKnight *knight) override;
};

class BaseBag {
  BaseKnight *knight;
  ItemType itemType;

protected:
  struct BagLList {
    BaseItem *item;
    BagLList *next;
    BagLList(BaseItem *it = nullptr, BagLList *ne = nullptr)
        : item(it), next(ne){};
    ~BagLList() {
      if (item)
        delete item;
    }
  };
  BagLList *head;
  int numItems, maxItems;

public:
  virtual bool insertFirst(BaseItem *item);
  virtual BaseItem *get(ItemType itemType);
  virtual bool GetItemtoUse(ItemType itemType, BaseKnight *knight);
  virtual bool CheckPhoenix(BaseKnight* knight); 
  virtual string toString() const;
  virtual void removeFirst();
  bool hasAntidote();
  ~BaseBag();
};

class DragonBag : public BaseBag {
public:
  DragonBag(BaseKnight *knight, int initialPhoenixI);
  bool insertFirst(BaseItem *item) override;
};

class PaladinBag : public BaseBag {
public:
  PaladinBag(BaseKnight *knight, int initialPhoenixI, int initialAntidote);
  bool insertFirst(BaseItem *item) override;
};

class LancelotBag : public BaseBag {
public:
  LancelotBag(BaseKnight *knight, int initialPhoenixI, int initialAntidote);
};

class NormalBag : public BaseBag {
public:
  NormalBag(BaseKnight *knight, int initialPhoenixI, int initialAntidote);
};

class BaseKnight {
protected:
  int id;
  int hp;
  int maxhp;
  int level;
  int gil;
  int antidote;
  int phoenixdownI;
  BaseBag *bag;
  KnightType knightType;

public:
  static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote,
                            int phoenixdownI);
  int getid() { return this->id; }
  void setHP(int HP) { this->hp = min(HP, 999); }
  int getHP() { return this->hp; }
  int getmaxHP() { return this->maxhp; }
  void setlevel(int level) { this->level = level; }
  int getlevel() { return this->level; }
  void setgil(int Gil) { this->gil = Gil; }
  int getgil() { return this->gil; }
  int getAntidote() { return this->antidote; }
  int getPhoenixI() { return this->phoenixdownI; }
  BaseBag *getbag() { return this->bag; }
  string toString() const;
  KnightType getKnightType() { return this->knightType; }
  virtual void attack(BaseOpponent *enemy) = 0;
  void healHP();
  virtual double getknightBaseDamage() = 0;
  virtual ~BaseKnight() = 0;
};

class PaladinKnight : public BaseKnight {
public:
  void attack(BaseOpponent *enemy) {
    switch (enemy->geteventID()) {
    case 1: {
      this->gil += 100;
      break;
    }
    case 2: {
      this->gil += 150;
      break;
    }
    case 3: {
      this->gil += 450;
      break;
    }
    case 4: {
      this->gil += 750;
      break;
    }
    case 5: {
      this->gil += 800;
      break;
    }
    case 6: {
      if (this->level >= enemy->LevelO()) {
        this->level = min(this->level + 1, 10);
        break;
      } else {
        if (this->bag->hasAntidote()) {
          bag->GetItemtoUse(ANTIDOTE, this);
        } else {
          for (int i = 0; i < 3; i++) {
            this->bag->removeFirst();
          }
          this->setHP(this->getHP() - 10);
          healHP();
        }
      }
      break;
    }
    case 7: {
      if (this->level >= enemy->LevelO()) {
        this->gil *= 2;
        break;
      } else {
        break;
      }
    }
    case 8: {
      if (this->getHP() < this->getmaxHP() / 3) {
        this->setHP(this->getHP() + this->getmaxHP() / 5);
      }
      break;
    }
    case 9: {
      this->setHP(this->getmaxHP());
      break;
    }
    }
  }
  double getknightBaseDamage() {
    return 0.06 * this->getHP() * this->getlevel();
  }
  PaladinKnight(int id, int hp, int maxhp, int level, int gil, int antidote,
                int phoenixdownI) {
    this->id = id;
    this->hp = hp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->bag = new PaladinBag(this, phoenixdownI, antidote);
    this->knightType = KnightType::PALADIN;
  }
};

class LancelotKnight : public BaseKnight {
public:
  void attack(BaseOpponent *enemy) {
    switch (enemy->geteventID()) {
    case 1: {
      this->gil += 100;
      break;
    }
    case 2: {
      this->gil += 150;
      break;
    }
    case 3: {
      this->gil += 450;
      break;
    }
    case 4: {
      this->gil += 750;
      break;
    }
    case 5: {
      this->gil += 800;
      break;
    }
    case 6: {
      if (this->level >= enemy->LevelO()) {
        this->level = min(this->level + 1, 10);
        break;
      } else {
        if (bag->hasAntidote()) {
          bag->GetItemtoUse(ANTIDOTE, this);
        } else {
          for (int i = 0; i < 3; i++) {
            this->bag->removeFirst();
          }
          this->setHP(this->getHP() - 10);
          healHP();
        }
      }
      break;
    }
    case 7: {
      if (this->level >= enemy->LevelO()) {
        this->gil *= 2;
        break;
      } else {
        this->gil /= 2;
      }
      break;
    }
    case 8: {
      if (this->gil < 50) {
        break;
      } else {
        if (this->getHP() < this->getmaxHP() / 3) {
          this->setgil(this->gil - 50);
          this->setHP(this->getHP() + this->getmaxHP() / 5);
        }
      }
      break;
    }
    case 9: {
      this->setHP(this->getmaxHP());
      break;
    }
    }
  }
  double getknightBaseDamage() {
    return 0.05 * this->getHP() * this->getlevel();
  }
  LancelotKnight(int id, int hp, int maxhp, int level, int gil, int antidote,
                 int phoenixdownI) {
    this->id = id;
    this->hp = hp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->bag = new LancelotBag(this, phoenixdownI, antidote);
    this->knightType = KnightType::LANCELOT;
  }
};

class DragonKnight : public BaseKnight {
private:
public:
  void attack(BaseOpponent *enemy) {
    switch (enemy->geteventID()) {
    case 1: {
      if (this->level >= enemy->LevelO()) {
        this->gil += 100;
        break;
      } else {
        this->hp -= 10 * (enemy->LevelO() - this->level);
        this->healHP();
      }
      break;
    }
    case 2: {
      if (this->level >= enemy->LevelO()) {
        this->gil += 150;
        break;
      } else {
        this->hp -= 15 * (enemy->LevelO() - this->level);
        this->healHP();
      }
      break;
    }
    case 3: {
      if (this->level >= enemy->LevelO()) {
        this->gil += 450;
        break;
      } else {
        this->hp -= 45 * (enemy->LevelO() - this->level);
        this->healHP();
      }
      break;
    }
    case 4: {
      if (this->level >= enemy->LevelO()) {
        this->gil += 750;
        break;
      } else {
        this->hp -= 75 * (enemy->LevelO() - this->level);
        this->healHP();
      }
      break;
    }
    case 5: {
      if (this->level >= enemy->LevelO()) {
        this->gil += 800;
        break;
      } else {
        this->hp -= 95 * (enemy->LevelO() - this->level);
        this->healHP();
      }
      break;
    }
    case 6: {
      if (this->level >= enemy->LevelO()) {
        this->level = min(this->level + 1, 10);
        break;
      } else {
        break;
      }
    }
    case 7: {
      if (this->level >= enemy->LevelO()) {
        this->gil *= 2;
        break;
      } else {
        this->gil /= 2;
      }
      break;
    }
    case 8: {
      if (this->gil < 50) {
        break;
      } else {
        if (this->getHP() < this->getmaxHP() / 3) {
          this->gil -= 50;
          this->setHP(this->getHP() + this->getmaxHP() / 5);
        }
      }
      break;
    }
    case 9: {
      this->setHP(this->getmaxHP());
      break;
    }
    }
  }
  double getknightBaseDamage() {
    return 0.075 * this->getHP() * this->getlevel();
  }
  DragonKnight(int id, int hp, int maxhp, int level, int gil, int antidote,
               int phoenixdownI) {
    this->id = id;
    this->hp = hp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->bag = new DragonBag(this, phoenixdownI);
    this->knightType = KnightType::DRAGON;
  }
};

class NormalKnight : public BaseKnight {
public:
  void attack(BaseOpponent *enemy) override {
    switch (enemy->geteventID()) {
    case 1: {
      if (this->level >= enemy->LevelO()) {
        this->gil += 100;
        break;
      } else {
        this->hp -= 10 * (enemy->LevelO() - this->level);
        this->healHP();
      }
      break;
    }
    case 2: {
      if (this->level >= enemy->LevelO()) {
        this->gil += 150;
        break;
      } else {
        this->hp -= 15 * (enemy->LevelO() - this->level);
        this->healHP();
      }
      break;
    }
    case 3: {
      if (this->level >= enemy->LevelO()) {
        this->gil += 450;
        break;
      } else {
        this->hp -= 45 * (enemy->LevelO() - this->level);
        this->healHP();
      }
      break;
    }
    case 4: {
      if (this->level >= enemy->LevelO()) {
        this->gil += 750;
        break;
      } else {
        this->hp -= 75 * (enemy->LevelO() - this->level);
        this->healHP();
      }
      break;
    }
    case 5: {
      if (this->level >= enemy->LevelO()) {
        this->gil += 800;
        break;
      } else {
        this->hp -= 95 * (enemy->LevelO() - this->level);
        this->healHP();
      }
      break;
    }
    case 6: {
      if (this->level >= enemy->LevelO()) {
        this->level = min(this->level + 1, 10);
      } else {
        if (bag->hasAntidote()) {
          bag->GetItemtoUse(ANTIDOTE, this);
        } else {
          for (int i = 0; i < 3; i++) {
            this->bag->removeFirst();
          }
          this->setHP(this->getHP() - 10);
          healHP();
        }
      }
      break;
    }
    case 7: {
      if (this->level >= enemy->LevelO()) {
        this->gil *= 2;
        break;
      } else {
        this->gil /= 2;
      }
      break;
    }
    case 8: {
      if (this->gil < 50) {
        break;
      } else {
        if (this->getHP() < this->getmaxHP() / 3) {
          this->gil -= 50;
          this->setHP(this->getHP() + this->getmaxHP() / 5);
        }
      }
      break;
    }
    case 9: {
      this->setHP(this->getmaxHP());
      break;
    }
    }
  }
  double getknightBaseDamage() override { return 1; }
  NormalKnight(int id, int hp, int maxhp, int level, int gil, int antidote,
               int phoenixdownI) {
    this->id = id;
    this->hp = hp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->bag = new NormalBag(this, phoenixdownI, antidote);
    this->knightType = KnightType::NORMAL;
  }
};

class ArmyKnights {
private:
  int knightID = 0;
  int numKnights, initialnumKnights;
  BaseKnight **knightInfo;
  bool win = false;
  static bool winOmegaWeapon, winHades, PaladinShield, LancelotSpear,
      GuinevereHair, ExcaliburSword;

public:
  ArmyKnights(const string &file_armyknights);
  ~ArmyKnights();
  BaseKnight *get(int i) { return knightInfo[i]; }
  bool fight(BaseOpponent *opponent);
  bool adventure(Events *events);
  void removeKnight(int i);
  bool faceToEvent(int orderOfEvent, int eventID);
  int count() const { return numKnights; }
  BaseKnight *lastKnight() const;
  bool isWinOmega();
  bool isWinHades();
  bool hasPaladinShield() const { return PaladinShield; }
  bool hasLancelotSpear() const { return LancelotSpear; }
  bool hasGuinevereHair() const { return GuinevereHair; }
  bool hasExcaliburSword() const { return ExcaliburSword; }
  void passGil(int remainGil, int beginPos);
  void printInfo() const;           
  void printResult(bool win) const; 
};

class KnightAdventure {
private:
  ArmyKnights *armyKnights;
  Events *events;

public:
  KnightAdventure();
  ~KnightAdventure();
  void loadArmyKnights(const string &s);
  void loadEvents(const string &s);
  void run();
};

#endif // __KNIGHT2_H__