#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Cr�e une fen�tre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Blaster X");

    // Charger une police
    sf::Font font;
    if (!font.loadFromFile("Neon Energy x.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
        return -1;
    }

    // Cr�er un objet texte
    sf::Text text;
    text.setFont(font);               // Associe la police
    text.setString("Space Blaster X");// D�finit le texte
    text.setCharacterSize(50);        // Taille du texte
    text.setFillColor(sf::Color::White); // Couleur du texte
    text.setStyle(sf::Text::Bold);    // Style (gras, italique, soulign�, etc.)
    text.setPosition(200, 250);       // Position dans la fen�tre

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer la fen�tre
        window.clear(sf::Color::Black);

        // Dessiner le texte
        window.draw(text);

        // Afficher le contenu
        window.display();
    }

    return 0;
}
