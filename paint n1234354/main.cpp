#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crée une fenêtre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Blaster X");

    // Charger une police
    sf::Font font;
    if (!font.loadFromFile("Neon Energy x.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
        return -1;
    }

    // Créer un objet texte
    sf::Text text;
    text.setFont(font);               // Associe la police
    text.setString("Space Blaster X");// Définit le texte
    text.setCharacterSize(50);        // Taille du texte
    text.setFillColor(sf::Color::White); // Couleur du texte
    text.setStyle(sf::Text::Bold);    // Style (gras, italique, souligné, etc.)
    text.setPosition(200, 250);       // Position dans la fenêtre

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer la fenêtre
        window.clear(sf::Color::Black);

        // Dessiner le texte
        window.draw(text);

        // Afficher le contenu
        window.display();
    }

    return 0;
}
