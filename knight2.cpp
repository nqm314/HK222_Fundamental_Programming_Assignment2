#include "knight2.h"

bool isPrime(int n) {
  if (n < 2)
    return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

bool isPaladin(int HP) {
  if (isPrime(HP))
    return true;
  else
    return false;
}

bool isLancelot(int HP) {
  if (HP == 888)
    return true;
  else
    return false;
}

bool isDragonKnight(int HP) {
  if (HP < 100 || HP > 999) {
    return false;
  }
  int a = HP % 10, b = (HP / 10) % 10, c = HP / 100;
  if (a == 0 || b == 0 || c == 0)
    return false;
  if (a * a == b * b + c * c || b * b == a * a + c * c ||
      c * c == a * a + b * b) {
    return true;
  }
  return false;
}

bool isNormalKnight(int HP) {
  if (isPaladin(HP) || isLancelot(HP) || isDragonKnight(HP))
    return false;
  return true;
}

/* * * BEGIN implementation of class BaseOpponent and derived classes * * */

/* * * END implementation of class BaseOpponent and derived classes * * */

/* * * BEGIN implementation of class BaseBag and derived classes * * */
bool BaseBag::insertFirst(BaseItem *item) {
  if (this->numItems >= maxItems) {
    return false;
  } else if (numItems == 0) {
    head = new BagLList(item);
    numItems++;
    return true;
  } else {
    BagLList *newItem = new BagLList(item, head);
    this->head = newItem;
    this->numItems++;
    return true;
  }
}
BaseItem *BaseBag::get(ItemType itemType) {
  if (numItems == 0)
    return nullptr;
  if (numItems == 1 && head->item->getItemType() == itemType) {
    return head->item;
  }
  BagLList *currItem = this->head;
  while (currItem) {
    if (currItem->item->getItemType() == itemType) {
      swap(head->item, currItem->item);
      return head->item;
    }
    currItem = currItem->next;
  }
  return nullptr;
}
bool BaseBag::GetItemtoUse(ItemType itemType, BaseKnight *knight) {
  BaseItem *it = knight->getbag()->get(itemType);
  if (it) {
    it->use(knight);
    head = head->next;
    numItems--;
    return true;
  }
  delete it;
  return false;
}
bool BaseBag::CheckPhoenix(BaseKnight *knight) {
  BagLList *tmp = head;
  while (tmp) {
    if (tmp->item->getItemType() == ItemType::PHOENIXDOWNI ||
        tmp->item->getItemType() == ItemType::PHOENIXDOWNII ||
        tmp->item->getItemType() == ItemType::PHOENIXDOWNIII ||
        tmp->item->getItemType() == ItemType::PHOENIXDOWNIV) {
      if (tmp->item->canUse(knight)) {
        if (GetItemtoUse(tmp->item->getItemType(), knight))
          return true;
      }
    }
    tmp = tmp->next;
  }
  return false;
}
string BaseBag::toString() const {
  if (numItems == 0)
    return "Bag[count=0;]";
  string show = "Bag[count=" + to_string(numItems) + ";";
  BagLList *currItem = head;
  while (currItem) {
    show += currItem->item->getTypeString() + ",";
    currItem = currItem->next;
  }
  show.erase(show.size() - 1);
  show += "]";
  return show;
}
void BaseBag::removeFirst() {
  if (numItems == 0)
    return;
  BagLList *tmp = head;
  head = head->next;
  delete tmp;
  numItems--;
}
bool BaseBag::hasAntidote() {
  BagLList *tmp = head;
  while (tmp) {
    if (tmp->item->getItemType() == ItemType::ANTIDOTE) {
      return true;
    }
    tmp = tmp->next;
  }
  return false;
}
BaseBag::~BaseBag() {
  while (head) {
    BagLList *curr = head;
    head = head->next;
    delete curr;
  }
  numItems = 0;
  delete knight;
}

DragonBag::DragonBag(BaseKnight *knight, int initialPhoenixI) {
  maxItems = 14;
  if (initialPhoenixI > 0) {
    for (int i = 0; i < initialPhoenixI; i++) {
      BaseItem *it;
      it = new PhoenixDownI();
      if (!(this->insertFirst(it)))
        delete it;
    }
  }
}
bool DragonBag::insertFirst(BaseItem *item) {
  if (item->getItemType() == ItemType::ANTIDOTE)
    return false;
  if (this->numItems >= maxItems) {
    return false;
  } else if (numItems == 0) {
    head = new BagLList(item, nullptr);
    numItems++;
    return true;
  } else {
    BagLList *newItem = new BagLList(item, head);
    this->head = newItem;
    this->numItems++;
    return true;
  }
}

PaladinBag::PaladinBag(BaseKnight *knight, int initialPhoenixI,
                       int initialAntidote) {
  if (initialPhoenixI > 0) {
    for (int i = 0; i < initialPhoenixI; i++) {
      BaseItem *it;
      it = new PhoenixDownI();
      if (!(this->insertFirst(it)))
        delete it;
    }
  }
  if (initialAntidote > 0) {
    for (int i = 0; i < initialAntidote; i++) {
      BaseItem *it;
      it = new Antidote();
      if (!(this->insertFirst(it)))
        delete it;
    }
  }
}
bool PaladinBag::insertFirst(BaseItem *item) {
  if (numItems == 0) {
    head = new BagLList(item, nullptr);
    numItems++;
    return true;
  }
  BagLList *newItem = new BagLList(item, head);
  this->head = newItem;
  this->numItems++;
  return true;
}

LancelotBag::LancelotBag(BaseKnight *knight, int initialPhoenixI,
                         int initialAntidote) {
  maxItems = 16;
  if (initialPhoenixI > 0) {
    for (int i = 0; i < initialPhoenixI; i++) {
      BaseItem *it;
      it = new PhoenixDownI();
      if (!(this->insertFirst(it)))
        delete it;
    }
  }
  if (initialAntidote > 0) {
    for (int i = 0; i < initialAntidote; i++) {
      BaseItem *it;
      it = new Antidote();
      if (!(this->insertFirst(it)))
        delete it;
    }
  }
}

NormalBag::NormalBag(BaseKnight *knight, int initialPhoenixI,
                     int initialAntidote) {
  maxItems = 19;
  if (initialPhoenixI > 0) {
    for (int i = 0; i < initialPhoenixI; i++) {
      BaseItem *it;
      it = new PhoenixDownI();
      if (!(this->insertFirst(it)))
        delete it;
    }
  }
  if (initialAntidote > 0) {
    for (int i = 0; i < initialAntidote; i++) {
      BaseItem *it;
      it = new Antidote();
      if (!(this->insertFirst(it)))
        delete it;
    }
  }
}
/* * * END implementation of class BaseBag and derived classes * * */

/* * * BEGIN implementation of class BaseItem and derived classes * * */
Antidote::Antidote() { this->itemtype = ItemType::ANTIDOTE; }
int Antidote::getnumAntidote() { return this->numAntidote; }

PhoenixDownI::PhoenixDownI() { this->itemtype = ItemType::PHOENIXDOWNI; }
bool PhoenixDownI::canUse(BaseKnight *knight) {
  if (knight->getHP() <= 0)
    return true;
  return false;
}
void PhoenixDownI::use(BaseKnight *knight) {
  if (canUse(knight)) {
    knight->setHP(knight->getmaxHP());
  }
}

PhoenixDownII::PhoenixDownII() { this->itemtype = ItemType::PHOENIXDOWNII; }
bool PhoenixDownII::canUse(BaseKnight *knight) {
  if (knight->getHP() < (knight->getmaxHP() / 4))
    return true;
  return false;
}
void PhoenixDownII::use(BaseKnight *knight) {
  if (canUse(knight)) {
    knight->setHP(knight->getmaxHP());
  }
}

PhoenixDownIII::PhoenixDownIII() { this->itemtype = ItemType::PHOENIXDOWNIII; }
bool PhoenixDownIII::canUse(BaseKnight *knight) {
  if (knight->getHP() < (knight->getmaxHP()) / 3)
    return true;
  return false;
}
void PhoenixDownIII::use(BaseKnight *knight) {
  if (canUse(knight)) {
    if (knight->getHP() <= 0)
      knight->setHP((knight->getmaxHP()) / 3);
    else {
      knight->setHP(knight->getHP() + (knight->getmaxHP()) / 4);
    }
  }
}

PhoenixDownIV::PhoenixDownIV() { this->itemtype = ItemType::PHOENIXDOWNIV; }
bool PhoenixDownIV::canUse(BaseKnight *knight) {
  if (knight->getHP() < knight->getmaxHP() / 2)
    return true;
  return false;
}
void PhoenixDownIV::use(BaseKnight *knight) {
  if (canUse(knight)) {
    if (knight->getHP() <= 0)
      knight->setHP((knight->getmaxHP()) / 2);
    else {
      knight->setHP(knight->getHP() + (knight->getmaxHP()) / 5);
    }
  }
}
/* * * END implementation of class BaseItem and derived classes * * */

/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil,
                               int antidote, int phoenixdownI) {
  BaseKnight *newKnight;
  if (isPaladin(maxhp)) {
    newKnight =
        new PaladinKnight(id, maxhp, maxhp, level, gil, antidote, phoenixdownI);
  } else if (isLancelot(maxhp)) {
    newKnight = new LancelotKnight(id, maxhp, maxhp, level, gil, antidote,
                                   phoenixdownI);
  } else if (isDragonKnight(maxhp)) {
    newKnight =
        new DragonKnight(id, maxhp, maxhp, level, gil, antidote, phoenixdownI);
  } else if (isNormalKnight(maxhp)) {
    newKnight =
        new NormalKnight(id, maxhp, maxhp, level, gil, antidote, phoenixdownI);
  }
  return newKnight;
}

string BaseKnight::toString() const {
  string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
  // inefficient version, students can change these code
  //      but the format output must be the same
  string s("");
  string bagString = (bag) ? bag->toString() : "Bag[count=0;]";
  s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) +
       ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) +
       ",gil:" + to_string(gil) + "," + bagString +
       ",knight_type:" + typeString[knightType] + "]";
  return s;
}

void BaseKnight::healHP() {
  if (this->bag->CheckPhoenix(this)) {
    return;
  } else if (this->getHP() <= 0 && this->gil >= 100) {
    this->gil -= 100;
    this->setHP(this->getmaxHP() / 2);
  }
  return; 
}

BaseKnight::~BaseKnight() { delete bag; }

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
bool ArmyKnights::winOmegaWeapon = false;
bool ArmyKnights::winHades = false;
bool ArmyKnights::PaladinShield = false;
bool ArmyKnights::LancelotSpear = false;
bool ArmyKnights::GuinevereHair = false;
bool ArmyKnights::ExcaliburSword = false;

ArmyKnights::ArmyKnights(const string &file_armyknights) {
  string line;
  ifstream armyknightsInput(file_armyknights);
  armyknightsInput >> numKnights;
  initialnumKnights = numKnights;
  getline(armyknightsInput, line);
  knightInfo = new BaseKnight *[numKnights];
  for (int i = 0; i < numKnights; i++) {
    getline(armyknightsInput, line);
    stringstream ss(line);
    int newhp, newlevel, newphoenixI, newgil, newantidote;
    ss >> newhp >> newlevel >> newphoenixI >> newgil >> newantidote;
    knightInfo[i] = BaseKnight::create(i + 1, newhp, newlevel, newgil,
                                       newantidote, newphoenixI);
  }
}

ArmyKnights::~ArmyKnights() {
  if (numKnights == 0)
    delete[] knightInfo;
  else {
    for (int i = 0; i < numKnights; i++) {
      if (knightInfo[i])
        delete knightInfo[i];
    }
    delete[] knightInfo;
    numKnights = 0;
  }
}

bool ArmyKnights::fight(BaseOpponent *opponent) {
  if (lastKnight()->getHP() <= 0)
    return false;
  else
    return true;
}

bool ArmyKnights::adventure(Events *events) {
  bool win = true;
  for (int i = 0; i < events->count(); i++) {
    if (!faceToEvent(i, events->get(i)))
      win = false;
    if (numKnights <= 0) {
      printInfo();
      break;
    }
    printInfo();
  }
  return win;
}

bool ArmyKnights::faceToEvent(int orderOfEvent, int eventID) {
  if (eventID == 1) {
    MadBear *mb = new MadBear();
    mb->setLevelO((orderOfEvent + eventID) % 10 + 1);
    for (int i = numKnights - 1; i >= 0; i--) {
      knightInfo[i]->attack(mb);
      if (!fight(mb)) {
        removeKnight(i);
        break;
      } else {
        if (knightInfo[i]->getgil() > 999) {
          int remainingGil = knightInfo[i]->getgil() - 999;
          knightInfo[i]->setgil(999);
          passGil(remainingGil, i - 1);
        }
        break;
      }
    }
    delete mb;
    if (numKnights == 0)
      return false;
    else
      return true;
  } else if (eventID == 2) {
    Bandit *bd = new Bandit();
    bd->setLevelO((orderOfEvent + eventID) % 10 + 1);
    for (int i = numKnights - 1; i >= 0; i--) {
      knightInfo[i]->attack(bd);
      if (!fight(bd)) {
        removeKnight(i);
        break;
      } else {
        if (knightInfo[i]->getgil() > 999) {
          int remainingGil = knightInfo[i]->getgil() - 999;
          knightInfo[i]->setgil(999);
          passGil(remainingGil, i - 1);
        }
        break;
      }
    }
    delete bd;
    if (numKnights == 0)
      return false;
    else
      return true;
  } else if (eventID == 3) {
    LordLupin *ll = new LordLupin();
    ll->setLevelO((orderOfEvent + eventID) % 10 + 1);
    for (int i = numKnights - 1; i >= 0; i--) {
      knightInfo[i]->attack(ll);
      if (!fight(ll)) {
        removeKnight(i);
        break;
      } else {
        if (knightInfo[i]->getgil() > 999) {
          int remainingGil = knightInfo[i]->getgil() - 999;
          knightInfo[i]->setgil(999);
          passGil(remainingGil, i - 1);
        }
        break;
      }
    }
    delete ll;
    if (numKnights == 0)
      return false;
    else
      return true;
  } else if (eventID == 4) {
    Elf *elf = new Elf();
    elf->setLevelO((orderOfEvent + eventID) % 10 + 1);
    for (int i = numKnights - 1; i >= 0; i--) {
      knightInfo[i]->attack(elf);
      if (!fight(elf)) {
        removeKnight(i);
        break;
      } else {
        if (knightInfo[i]->getgil() > 999) {
          int remainingGil = knightInfo[i]->getgil() - 999;
          knightInfo[i]->setgil(999);
          passGil(remainingGil, i - 1);
        }
        break;
      }
    }
    delete elf;
    if (numKnights == 0)
      return false;
    else
      return true;
  } else if (eventID == 5) {
    Troll *troll = new Troll();
    troll->setLevelO((orderOfEvent + eventID) % 10 + 1);
    for (int i = numKnights - 1; i >= 0; i--) {
      knightInfo[i]->attack(troll);
      if (!fight(troll)) {
        removeKnight(i);
        break;
      } else {
        if (knightInfo[i]->getgil() > 999) {
          int remainingGil = knightInfo[i]->getgil() - 999;
          knightInfo[i]->setgil(999);
          passGil(remainingGil, i - 1);
        }
        break;
      }
    }
    delete troll;
    if (numKnights == 0)
      return false;
    else
      return true;
  } else if (eventID == 6) {
    Tornbery *tb = new Tornbery();
    tb->setLevelO((orderOfEvent + eventID) % 10 + 1);
    for (int i = numKnights - 1; i >= 0; i--) {
      knightInfo[i]->attack(tb);
      if (!fight(tb)) {
        removeKnight(i);
        break;
      } else {
        if (knightInfo[i]->getgil() > 999) {
          int remainingGil = knightInfo[i]->getgil() - 999;
          knightInfo[i]->setgil(999);
          passGil(remainingGil, i - 1);
        }
        break;
      }
    }
    delete tb;
    if (numKnights == 0)
      return false;
    else
      return true;
  } else if (eventID == 7) {
    QueenOfCards *queen = new QueenOfCards();
    queen->setLevelO((orderOfEvent + eventID) % 10 + 1);
    lastKnight()->attack(queen);
    if (lastKnight()->getgil() > 999) {
      int remainGil = lastKnight()->getgil() - 999;
      lastKnight()->setgil(999);
      passGil(remainGil, numKnights - 2);
    }
    delete queen;
    return true;
  } else if (eventID == 8) {
    NinaDeRings *nina = new NinaDeRings();
    lastKnight()->attack(nina);
    return true;
  } else if (eventID == 9) {
    DurianGarden *dg = new DurianGarden();
    lastKnight()->attack(dg);
    return true;
  } else if (eventID == 10) {
    return isWinOmega();
  } else if (eventID == 11) {
    return isWinHades();
  } else if (eventID == 112) {
    BaseItem *it = new PhoenixDownII();
    for (int i = numKnights - 1; i >= 0; i--) {
      if (knightInfo[i]->getbag()->insertFirst(it))
        break;
    }
    return true;
  } else if (eventID == 113) {
    BaseItem *it = new PhoenixDownIII();
    for (int i = numKnights - 1; i >= 0; i--) {
      if (knightInfo[i]->getbag()->insertFirst(it))
        break;
    }
    return true;
  } else if (eventID == 114) {
    BaseItem *it = new PhoenixDownIV();
    for (int i = numKnights - 1; i >= 0; i--) {
      if (knightInfo[i]->getbag()->insertFirst(it))
        break;
    }
    return true;
  } else if (eventID == 95) {
    PaladinShield = true;
  } else if (eventID == 96) {
    LancelotSpear = true;
  } else if (eventID == 97) {
    GuinevereHair = true;
  } else if (eventID == 98) {
    if (PaladinShield && LancelotSpear && GuinevereHair) {
      ExcaliburSword = true;
    }
  } else if (eventID == 99) {
    if (hasExcaliburSword())
      return true;
    if (!hasGuinevereHair() && !hasLancelotSpear() && !hasPaladinShield()) {
      for (int i = numKnights - 1; i >= 0; i--) {
        removeKnight(i);
      }
      return false;
    }
    int UltimeciaHP = 5000;
    for (int i = numKnights - 1; i >= 0; i--) {
      if (knightInfo[i]->getKnightType() != KnightType::NORMAL) {
        double damage = knightInfo[i]->getknightBaseDamage();
        UltimeciaHP -= damage;
        if (UltimeciaHP <= 0)
          return true;
        removeKnight(i);
      } else {
        removeKnight(i);
      }
    }
    return false;
  }
  return true;
}

void ArmyKnights::removeKnight(int i) {
  if (knightInfo && knightInfo[i])
    delete knightInfo[i];
  numKnights--;
}

BaseKnight *ArmyKnights::lastKnight() const {
  if (!ArmyKnights::count()) {
    return NULL;
  } else
    return (knightInfo[numKnights - 1]);
}

bool ArmyKnights::isWinOmega() {
  if (winOmegaWeapon)
    return true;
  for (int i = numKnights - 1; i >= 0; i--) {
    if (knightInfo[i]->getlevel() == 10 && knightInfo[i]->getHP() == knightInfo[i]->getmaxHP() ||
        knightInfo[i]->getKnightType() == KnightType::DRAGON) {
      winOmegaWeapon = true;
      knightInfo[i]->setgil(999);
      knightInfo[i]->setlevel(10);
      return true;
    } else {
      knightInfo[i]->setHP(0);
      knightInfo[i]->healHP();
      if (knightInfo[i]->getHP() <= 0) {
        removeKnight(i);
        break;
      } else
        return true;
    }
  }
  if (numKnights <= 0)
    return false;
  return true;
}

bool ArmyKnights::isWinHades() {
  if (winHades)
    return true;
  for (int i = numKnights - 1; i >= 0; i--) {
    if (knightInfo[i]->getlevel() == 10 ||
        knightInfo[i]->getKnightType() == KnightType::PALADIN &&
            knightInfo[i]->getlevel() >= 8) {
      winHades = true;
      PaladinShield = true;
      return true;
    } else {
      knightInfo[i]->setHP(0);
      knightInfo[i]->healHP();
      if (knightInfo[i]->getHP() <= 0) {
        removeKnight(i);
        break;
      } else
        return true;
    }
  }
  if (numKnights <= 0)
    return false;
  return true;
}

void ArmyKnights::passGil(int remainGil, int beginPos) {
  while (remainGil > 0 && beginPos >= 0) {
    int currKnightGil = knightInfo[beginPos]->getgil();
    currKnightGil += remainGil;
    remainGil = 0;
    if (currKnightGil > 999) {
      remainGil = currKnightGil - 999;
      currKnightGil = 999;
    }
    knightInfo[beginPos]->setgil(currKnightGil);
    beginPos--;
  }
}

void ArmyKnights::printInfo() const {
  cout << "No. knights: " << this->count();
  if (this->count() > 0) {
    BaseKnight *lknight = lastKnight(); // last knight
    cout << ";" << lknight->toString();
  }
  cout << ";PaladinShield:" << this->hasPaladinShield()
       << ";LancelotSpear:" << this->hasLancelotSpear()
       << ";GuinevereHair:" << this->hasGuinevereHair()
       << ";ExcaliburSword:" << this->hasExcaliburSword() << endl
       << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
  cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
  armyKnights = nullptr;
  events = nullptr;
}

KnightAdventure::~KnightAdventure() {
  delete armyKnights;
  delete events;
}

void KnightAdventure::loadArmyKnights(const string &armyknights) {
  armyKnights = new ArmyKnights(armyknights);
}

void KnightAdventure::loadEvents(const string &eve) { events = new Events(eve); }

void KnightAdventure::run() {
  if (armyKnights && events) {
    armyKnights->ArmyKnights::printResult(armyKnights->adventure(events));
  }
}

/* * * END implementation of class KnightAdventure * * */