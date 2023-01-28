#include "Card.hpp"
#include "Board.hpp"
#include "AssetsManager.hpp"
#include "GameManager.hpp"
#include "EventManager.hpp"
#include "InputManager.hpp"
#include "Ball.hpp"

using namespace std;
using namespace sf;

Card::Card()
{
	isInitialized = false;
	isSleeping = true;
	haveTheBall = false;
}

Card::Card(string name, string description, int attack, int defence, int cost, CardType cardType, string textureName, bool isPLayerOneCard)
{
	this->name(name); this->description(description); this->attack(attack); this->defence(defence);
	this->cardType(cardType); this->cost(cost);
	isOnBoard = false;

	Texture& tmpText = AssetsManager::Instance().GetTexture(textureName);
	this->fanArt.setTexture(tmpText);
	this->fanArt.setOrigin(tmpText.getSize().x * 0.5f, tmpText.getSize().y * 0.5f);

	Texture& tmpText2 = AssetsManager::Instance().GetTexture("Card");
	this->bg.setTexture(tmpText2);
	this->bg.setOrigin(tmpText2.getSize().x * 0.5f, tmpText2.getSize().y * 0.5f);

	Texture& tmpText3 = AssetsManager::Instance().GetTexture("Attack");
	this->attackSprite.setTexture(tmpText3);
	this->attackSprite.setOrigin(tmpText3.getSize().x * 0.5f, tmpText3.getSize().y * 0.5f);

	Texture& tmpText4 = AssetsManager::Instance().GetTexture("Defence");
	this->defenceSprite.setTexture(tmpText4);
	this->defenceSprite.setOrigin(tmpText4.getSize().x * 0.5f, tmpText4.getSize().y * 0.5f);

	Texture& tmpText5 = AssetsManager::Instance().GetTexture("Mana");
	this->manaSprite.setTexture(tmpText5);
	this->manaSprite.setOrigin(tmpText5.getSize().x * 0.5f, tmpText5.getSize().y * 0.5f);

	this->nameText.setFont(AssetsManager::Instance().GetFont("poppins"));
	this->nameText.setFillColor(Color::White);
	this->nameText.setCharacterSize(35);

	this->descrptionText.setFont(AssetsManager::Instance().GetFont("poppins"));
	this->descrptionText.setFillColor(Color::White);
	this->descrptionText.setCharacterSize(15);

	this->id = GetUniqueId();
	this->isInitialized = true;
	this->isSelected = false;
	this->isPlayerOneCard = isPlayerOneCard;
	this->haveTheBall = false;
	this->isSleeping = true;
	this->attackBonus = this->defenceBonus = this->costBonus = 0;
}

Card::Card(string name, string description, int attack, int defence, int cost, CardType cardType, string textureName, bool isPLayerOneCard, Effect* effect)
	: Card(name, description, attack, defence, cost, cardType, textureName, isPlayerOneCard)
{
	AddEffect(effect);
}


Card::Card(const Card& card)
{
	this->name(card._name); this->description(card._description); this->attack(card._attack); this->defence(card._defence);
	this->cardType(card._cardType); this->cost(card._cost);
	isOnBoard = card.isOnBoard;
	this->fanArt = Sprite(card.fanArt);
	this->bg = Sprite(card.bg);
	this->attackSprite = Sprite(card.attackSprite);
	this->defenceSprite = Sprite(card.defenceSprite);
	this->manaSprite = Sprite(card.manaSprite);
	this->id = card.id;
	this->isInitialized = card.isInitialized;
	this->isSelected = card.isSelected;
	this->isPlayerOneCard = card.isPlayerOneCard;
	this->haveTheBall = card.haveTheBall;
	this->cardPlaceInfo = CardPlaceInfo(card.cardPlaceInfo);
	this->isSleeping = card.isSleeping;
	this->attackBonus = card.attackBonus;
	this->defenceBonus = card.defenceBonus;
	this->attackText = Text(card.attackText);
	this->defenceText = Text(card.defenceText);
	this->costText = Text(card.costText);
	this->costBonus = card.costBonus;
	this->rectangleToDraw = Rectangle(card.rectangleToDraw);
	this->nameText = Text(card.nameText);
	this->descrptionText = Text(card.descrptionText);

	for (int i = 0; i < card.effects.size(); i++)
	{
		this->AddEffect(card.effects[i]->Clone());
	}
}

int Card::GetUniqueId()
{
	static int id = -1;
	id++;
	return id;
}

Font& Card::GetCardFont()
{
	return AssetsManager::Instance().GetFont("poppins");
}

void Card::CalculateCardBoardTransform()
{
	if (isOnBoard)
	{
		rectangleToDraw = Rectangle(this->cardPlaceInfo.hitbox);
	}

	SetPosition(rectangleToDraw.center);
	SetSize(rectangleToDraw.size);
}

Vector2f Card::GetPosition()
{
	return rectangleToDraw.center;
}

void Card::SetPosition(const Vector2f& position)
{
	this->rectangleToDraw.center = position;
}

Vector2f Card::GetSize()
{
	return isOnBoard ? cardPlaceInfo.hitbox.size : rectangleToDraw.size;
}

void Card::SetSize(const Vector2f& size)
{
	if (!isInitialized)
		return;
	rectangleToDraw.size = size;
}

Rectangle Card::GetHitbox()
{
	return Rectangle(GetPosition(), GetSize());
}

void Card::AddEffect(Effect* effect)
{
	effect->card = this;
	this->effects.push_back(effect);
}

bool Card::CanPlaceInBoard(bool playerOneBoard, CardType line, int index) const
{
	if (this->_cardType != line)
	{
		return false;
	}
	return true;
}

bool Card::CanAttack(const CardPlaceInfo& thisCardInfo, const CardPlaceInfo& defencerInfo)
{
	return true;
}

bool Card::CanDefend(const CardPlaceInfo& thisCardInfo, const CardPlaceInfo& strikerInfo)
{
	return true;
}

void Card::GetCardsCanAttack(vector<CardPlaceInfo>& cardsCanAttackInfo)
{
	Board::Instance().GetAdjacentCardsPlacesInfo(cardPlaceInfo, cardsCanAttackInfo);
	for (int i = cardsCanAttackInfo.size() - 1; i >= 0; i--)
	{
		if (!cardsCanAttackInfo[i].card->isInitialized || !cardsCanAttackInfo[i].card->isOnBoard || cardsCanAttackInfo[i].card->isPlayerOneCard == cardPlaceInfo.card->isPlayerOneCard
			|| (!haveTheBall && !cardsCanAttackInfo[i].card->haveTheBall))
		{
			cardsCanAttackInfo.erase(cardsCanAttackInfo.begin() + i);
		}
	}
}

void Card::GetPlaceToMove(vector<CardPlaceInfo>& placeCanMove)
{
	Board::Instance().GetAdjacentCardsPlacesInfo(cardPlaceInfo, placeCanMove);
	for (int i = placeCanMove.size() - 1; i >= 0; i--)
	{
		if (placeCanMove[i].card->isInitialized)
		{
			placeCanMove.erase(placeCanMove.begin() + i);
		}
	}
}

void Card::OnPlaceOnBoard()
{
	isSleeping = true;
	isSelected = false;

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->card = this;
	}
}

void Card::OnBeginTurn(bool isPlayerOneTurn)
{
	if (isInitialized)
	{
		isSleeping = false;

		for (int i = 0; i < effects.size(); i++)
		{
			effects[i]->OnBeginTurn(isPlayerOneTurn);
		}
	}
}

void Card::OnEndTurn(bool playerOneEndTurn)
{
	isSelected = false;
}

void Card::OnMove()
{
	isSleeping = true;
	isSelected = false;
}

void Card::OnMakeDuel(const CardPlaceInfo& striker, const CardPlaceInfo& defender)
{

}

void Card::Update(RenderWindow& window)
{
	if (!isInitialized)
		return;

	CalculateCardBoardTransform();
	if (isOnBoard)
	{
		if (isSelected)
		{
			if (!isSleeping)
			{
				GetCardsCanAttack(cardsCanAttack);
				if (cardsCanAttack.size() > 0 && InputManager::Instance().GetKeyDown(Mouse::Button::Left))
				{
					for (int i = 0; i < cardsCanAttack.size(); i++)
					{
						CardPlaceInfo* tmpCard = &cardsCanAttack[i];
						if (tmpCard->hitbox.Contains(InputManager::Instance().MousePosition()))
						{
							Board::Instance().MakeDuel(this->cardPlaceInfo, *tmpCard);
						}
					}
				}

				GetPlaceToMove(placeToMove);
				if (InputManager::Instance().GetKeyDown(Mouse::Button::Left))
				{
					for (int i = 0; i < placeToMove.size(); i++)
					{
						if (placeToMove[i].hitbox.Contains(InputManager::Instance().MousePosition()))
						{
							bool targetHaveTheBall = placeToMove[i].card->haveTheBall;
							Card* targetCard = placeToMove[i].card;
							Board::Instance().SwitchCards(cardPlaceInfo, placeToMove[i]);
							if (targetHaveTheBall || targetCard->haveTheBall)
							{
								Ball::Instance().SetAttachCard(*targetCard);
								this->haveTheBall = false;
							}
							OnMove();
						}
					}
				}
			}
		}
	}
}

void Card::Draw(RenderWindow& window)
{
	if (!isInitialized)
		return;

	Vector2f pos = rectangleToDraw.center;
	Vector2f size = rectangleToDraw.size;
	if (isOnBoard)
	{
		this->manaSprite.setPosition(pos + Vector2f(manaRec.center.x * size.x, manaRec.center.y * size.y));
		this->manaSprite.setScale(Vector2f((size.x * manaRec.size.x) / manaSprite.getTextureRect().width, (size.y * manaRec.size.y) / manaSprite.getTextureRect().height));

		this->defenceSprite.setPosition(pos + Vector2f(defenceRec.center.x * size.x, defenceRec.center.y * size.y));
		this->defenceSprite.setScale(Vector2f((size.x * defenceRec.size.x) / defenceSprite.getTextureRect().width, (size.y * defenceRec.size.y) / defenceSprite.getTextureRect().height));

		this->attackSprite.setPosition(pos + Vector2f(attackRec.center.x * size.x, attackRec.center.y * size.y));
		this->attackSprite.setScale(Vector2f((size.x * attackRec.size.x) / attackSprite.getTextureRect().width, (size.y * attackRec.size.y) / attackSprite.getTextureRect().height));

		this->fanArt.setPosition(pos);
		this->fanArt.setScale(Vector2f(size.x / fanArt.getTextureRect().width, size.y/ fanArt.getTextureRect().height));

		window.draw(fanArt);
		window.draw(attackSprite);
		window.draw(defenceSprite);
		window.draw(manaSprite);
	}
	else
	{
		this->manaSprite.setPosition(pos + Vector2f(manaRec.center.x * size.x, manaRec.center.y * size.y));
		this->manaSprite.setScale(Vector2f((size.x * manaRec.size.x) / manaSprite.getTextureRect().width, (size.y * manaRec.size.y) / manaSprite.getTextureRect().height));

		this->defenceSprite.setPosition(pos + Vector2f(defenceRec.center.x * size.x, defenceRec.center.y * size.y));
		this->defenceSprite.setScale(Vector2f((size.x * defenceRec.size.x) / defenceSprite.getTextureRect().width, (size.y * defenceRec.size.y) / defenceSprite.getTextureRect().height));

		this->attackSprite.setPosition(pos + Vector2f(attackRec.center.x * size.x, attackRec.center.y * size.y));
		this->attackSprite.setScale(Vector2f((size.x * attackRec.size.x) / attackSprite.getTextureRect().width, (size.y * attackRec.size.y) / attackSprite.getTextureRect().height));

		this->fanArt.setPosition(pos + Vector2f(fanArtRec.center.x * size.x, fanArtRec.center.y * size.y));
		this->fanArt.setScale(Vector2f((size.x * fanArtRec.size.x) / fanArt.getTextureRect().width, (size.y * fanArtRec.size.y) / fanArt.getTextureRect().height));

		this->bg.setPosition(pos);
		this->bg.setScale(Vector2f(size.x / bg.getTextureRect().width, size.y / bg.getTextureRect().height));

		window.draw(fanArt);
		window.draw(bg);
	}

	if (isSelected)
	{
		Rectangle::DrawWire(window, GetHitbox(), Color::Yellow);
	}


	if (isSelected)
	{
		for (int i = 0; i < placeToMove.size(); i++)
		{
			Rectangle::Draw(window, placeToMove[i].hitbox * 0.8, Color::Green);
		}
	}

	if (isSelected)
	{
		for (int i = 0; i < cardsCanAttack.size(); i++)
		{
			Rectangle::DrawWire(window, cardsCanAttack[i].hitbox * 1.2, Color::Red);
		}
	}

	if (isPlayerOneCard == Board::Instance().player1.isMyTurn || isOnBoard)
	{
		//Draw the text
		attackText.setString(to_string(_attack + attackBonus));
		Color color = attackBonus > 0 ? Color::Green : (attackBonus < 0 ? Color::Red : Color::White);
		attackText.setFillColor(color);
		attackText.setOutlineColor(color);
		attackText.setOrigin(Vector2f(attackText.getLocalBounds().width * 0.5f, attackText.getLocalBounds().height * 0.5f));
		attackText.setPosition(pos + Vector2f(attackRec.center.x * size.x, attackRec.center.y * size.y));
		attackText.setFont(GetCardFont());
		attackText.setCharacterSize(50);
		window.draw(attackText);

		defenceText.setString(to_string(_defence + defenceBonus));
		color = defenceBonus > 0 ? Color::Green : (defenceBonus < 0 ? Color::Red : Color::White);
		defenceText.setFillColor(color);
		defenceText.setOutlineColor(color);
		defenceText.setOrigin(Vector2f(defenceText.getLocalBounds().width * 0.5f, defenceText.getLocalBounds().height * 0.5f));
		defenceText.setPosition(pos + Vector2f(defenceRec.center.x * size.x, defenceRec.center.y * size.y));
		defenceText.setFont(GetCardFont());
		defenceText.setCharacterSize(50);
		window.draw(defenceText);

		costText.setString(to_string(_cost + costBonus));
		color = costBonus > 0 ? Color::Green : (costBonus < 0 ? Color::Red : Color::White);
		costText.setFillColor(color);
		costText.setOutlineColor(color);
		costText.setOrigin(Vector2f(costText.getLocalBounds().width * 0.5f, costText.getLocalBounds().height * 0.5f));
		costText.setPosition(pos + Vector2f(manaRec.center.x * size.x * 1.05, manaRec.center.y * size.y * 1.1));
		costText.setFont(GetCardFont());
		costText.setCharacterSize(65);
		window.draw(costText);
	}

	if (isPlayerOneCard == Board::Instance().player1.isMyTurn && !isOnBoard)
	{
		this->nameText.setString(name());
		this->nameText.setOrigin(nameText.getLocalBounds().width * 0.5, nameText.getLocalBounds().height * 0.5);
		this->nameText.setPosition(pos + Vector2f(nameRec.center.x * size.x, nameRec.center.y * size.y));

		this->descrptionText.setString(description());
		this->descrptionText.setOrigin(descrptionText.getLocalBounds().width * 0.5, descrptionText.getLocalBounds().height * 0.5);
		this->descrptionText.setPosition(pos + Vector2f(descriptionRec.center.x * size.x, descriptionRec.center.y * size.y));

		window.draw(nameText);
		window.draw(descrptionText);
	}
}

string Card::ToString() const
{
	ostringstream os;
	os << "[Card], name : " << this->_name;
	return os.str();
}

Card::~Card()
{
	
}