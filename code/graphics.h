#include "triangle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>
#include <iostream>

sf::Sprite getSprite(sf::RenderTexture& rt) {
	sf::Sprite s;
	s.setTexture(rt.getTexture());
	return s;
}

void displayScreen(sf::RenderTexture& screen) {
	sf::RenderWindow window(sf::VideoMode(screen.getSize().x, screen.getSize().y), "Current Screen", sf::Style::None);
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		window.draw(getSprite(screen));

		window.display();
	}
}

sf::RenderTexture& initializeScreen(sf::RenderTexture& screen) {

	sf::RectangleShape rect(sf::Vector2f(screen.getSize()));
	rect.setFillColor(sf::Color(30, 30, 30));
	rect.setPosition(0, 0);
	screen.draw(rect);

	rect.setSize(sf::Vector2f(screen.getSize().x-4, screen.getSize().y-4));
	rect.setPosition(2, 2);
	rect.setFillColor(sf::Color(140, 140, 140));
	screen.draw(rect);

	rect.setSize(sf::Vector2f(screen.getSize().x-12, screen.getSize().y-12));
	rect.setPosition(6, 6);
	rect.setFillColor(sf::Color::Black);
	screen.draw(rect);

	//displayScreen(screen);

	return screen;
}
sf::RenderTexture& drawStructure(sf::RenderTexture& screen, std::vector<Triangle>& triangulation) {
	std::vector<Vertex> vs;
	std::vector<Edge> es;
	for(Triangle& t : triangulation) {
		vs.push_back(t.p1); vs.push_back(t.p2); vs.push_back(t.p3);
		es.push_back(t.e1); es.push_back(t.e2); es.push_back(t.e3);
	}

	std::vector<sf::RectangleShape> squares;
	for(const auto& v : vs) {
		sf::RectangleShape p(sf::Vector2f(5,5));
		p.setPosition(v.x-3, v.y-3);
		p.setFillColor(sf::Color::White);
		squares.push_back(p);
	}
	sf::VertexArray lines(sf::Lines, 2 * es.size());
	for(int a = 0; a < es.size(); a++) {
		lines[2*a].position.x = es[a].p1.x;
		lines[2*a].position.y = es[a].p1.y;
		lines[2*a].color = sf::Color::Red;

		lines[2*a+1].position.x = es[a].p2.x;
		lines[2*a+1].position.y = es[a].p2.y;
		lines[2*a+1].color = sf::Color::Red;
	}

	screen.draw(lines);

	for(const auto& s : squares) {
		screen.draw(s);
	}
}
void displayGraph(std::vector<Vertex> points) {

	sf::RenderWindow window(sf::VideoMode(800, 600), "Graph");

	std::vector<sf::RectangleShape*> squares;
	for(const auto p : points) {
		sf::RectangleShape* c1 = new sf::RectangleShape(sf::Vector2f(4,4));
		c1->setPosition(p.x, p.y);
		squares.push_back(c1);
	}

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for(const auto &s : squares) {
			window.draw(*s);
		}

		window.display();
	}
}

