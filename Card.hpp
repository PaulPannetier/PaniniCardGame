#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include "Useful.hpp"
#include "Collider2D.hpp"
#include "CardPlaceInfo.hpp"
#include "Effect.hpp"

class Card : Object
{
private:

	//proportion des tailles des différentss élément de la carte
	Rectangle manaRec = Rectangle(sf::Vector2f(-0.372, -0.42), sf::Vector2f(0.25, 0.182));
	Rectangle defenceRec = Rectangle(sf::Vector2f(0.37, 0.4), sf::Vector2f(0.25, 0.182));
	Rectangle attackRec = Rectangle(sf::Vector2f(-0.371, 0.4), sf::Vector2f(0.25, 0.182));
	Rectangle fanArtRec = Rectangle(sf::Vector2f(0, -0.230), sf::Vector2f(0.7001, 0.440));
	Rectangle descriptionRec = Rectangle(sf::Vector2f(0, 0.271f), sf::Vector2f(0.614f, 0.195f));
	Rectangle nameRec = Rectangle(sf::Vector2f(0, 0.00475f), sf::Vector2f(0.7, 0.0569f));

	std::string _name;//le nom du joueur
	std::string _description;//description des effets
	int _attack, _defence;//stats d'attaque et de defence
	int _cost;//le cout en point de la carte
	CardType _cardType;//le type de carte (goal, attaquant, defenceur ou sort)
	std::vector<Effect*> effects;
	sf::Sprite fanArt;//le sprite (servant a laffichage de l'image)
	sf::Sprite bg;//le fond de l'image
	sf::Sprite manaSprite;//le cout en mana
	sf::Sprite attackSprite;//l'icone de l'attaque
	sf::Sprite defenceSprite;//l'icone de defence
	sf::Text nameText, descrptionText;

	std::vector<CardPlaceInfo> placeToMove, cardsCanAttack;

	int GetUniqueId();
	static sf::Font& GetCardFont();

public:
	int id;//l'identifiant unique de la carte
	bool isOnBoard;//true si elle est posé sur le plateau, false si elle est dans la main ou le deck
	bool isInitialized;//true si tout les attribut ont été affecté, false sinon
	bool isSelected;//est selectionner sur le plateau de jeu ou dans la main
	bool isPlayerOneCard;//si cette carte appartient au joueur 1
	CardPlaceInfo cardPlaceInfo;//les info sur lemplacement ou est posé la carte
	bool haveTheBall, isSleeping;//si la carte possède le ballon, si la carte est endormi (cad si elle peut effectuer une action se tour)
	int attackBonus, defenceBonus, costBonus;
	sf::Text attackText, defenceText, costText;
	Rectangle rectangleToDraw;

	Card();
	Card(std::string name, std::string description, int attack, int defence, int cost, CardType cardType, std::string textureName, bool isPlayerOneCard = false);
	Card(std::string name, std::string description, int attack, int defence, int cost, CardType cardType, std::string textureName, bool isPlayerOneCard, Effect* effet);
	Card(const Card& card);

	//Getter:
	std::string name() { return _name; }
	std::string description() { return _description; }
	int attack() { return _attack; } int defence() { return _defence; } int cost() { return _cost; }
	CardType cardType() { return _cardType; }
	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
	Rectangle GetHitbox();

	//Setter:
	void name(std::string value) { _name = value; }
	void description(std::string value) { _description = value; }
	void attack(int value) { _attack = value; } void defence(int value) { _defence = value; }
	void cost(int value) { _cost = value; }
	void cardType(CardType value) { _cardType = value; }
	void SetPosition(const sf::Vector2f& position);
	void SetSize(const sf::Vector2f& size);
	void AddEffect(Effect* effect);

	virtual void GetCardsCanAttack(std::vector<CardPlaceInfo>& cardsCanAttackInfo);
	virtual void GetPlaceToMove(std::vector<CardPlaceInfo>& placeCanMove);
	virtual bool CanPlaceInBoard(bool playerOneBoard, CardType line, int index) const;
	virtual bool CanAttack(const CardPlaceInfo& thisCardInfo, const CardPlaceInfo& defencerInfo);
	virtual bool CanDefend(const CardPlaceInfo& thisCardInfo, const CardPlaceInfo& strikerInfo);

	virtual void OnPlaceOnBoard();
	virtual void OnMove();
	virtual void OnBeginTurn(bool playerOneTurn);
	virtual void OnEndTurn(bool playerOneEndTurn);
	virtual void OnMakeDuel(const CardPlaceInfo& striker, const CardPlaceInfo& defender);

	void CalculateCardBoardTransform();
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	std::string ToString() const override;

	~Card();
};

#endif

