#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include "Useful.hpp"
#include "Collider2D.hpp"
#include "CardPlaceInfo.hpp"

class Card : Object
{
private:
	std::string _name;//le nom du joueur
	std::string _description;//description des effets
	int _attack, _defence;//stats d'attaque et de defence
	int _cost;//le cout en point de la carte
	CardType _cardType;//le type de carte (goal, attaquant, defenceur ou sort)
	sf::Sprite sprite;//le sprite (servant a laffichage de l'image)

	int GetUniqueId();

public:
	int id;//l'identifiant unique de la carte
	bool isOnBoard;//true si elle est posé sur le plateau, false si elle est dans la main ou le deck
	bool isInitialized;//true si tout les attribut ont été affecté, false sinon
	bool isSelected;//est selectionner sur le plateau de jeu ou dans la main
	bool isPlayerOneCard;//si cette carte appartient au joueur 1
	CardPlaceInfo cardPlaceInfo;

	Card();
	Card(std::string name, std::string description, int attack, int defence, int cost, CardType cardType, std::string textureName, bool isPlayerOneCard = false);
	Card(const Card& card);

	//Getter:
	std::string name() { return _name; }
	std::string description() { return _description; }
	int attack() { return _attack; } int defence() { return _defence; } int cost() { return _cost; }
	CardType cardType() { return _cardType; }
	sf::Vector2f GetPosition();
	float GetRotation();
	sf::Vector2f GetSize();
	Rectangle GetHitbox();

	//Setter:
	void name(std::string value) { _name = value; }
	void description(std::string value) { _description = value; }
	void attack(int value) { _attack = value; } void defence(int value) { _defence = value; }
	void cost(int value) { _cost = value; }
	void cardType(CardType value) { _cardType = value; }
	void SetPosition(const sf::Vector2f& position);
	void SetRotation(float angle);
	void SetSize(const sf::Vector2f& size);
	void InverseScale(bool x, bool y);

	bool CanPlaceInBoard(bool playerOneBoard, CardType line, int index) const;
	bool CanAttack(const CardPlaceInfo& thisCardInfo, const CardPlaceInfo& defencerInfo);
	bool CanDefend(const CardPlaceInfo& thisCardInfo, const CardPlaceInfo& strikerInfo);

	void CalculateCardBoardTransform();
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	std::string ToString() const override;
};

#endif

