#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(1920, 1080), "Paint pour les nuls");
    window.setFramerateLimit(60);

    vector<CircleShape> shapes;

    Color currentColor = Color::Black;
    float brushSize = 5.0f;
    bool eraserMode = false;

    Texture redTexture;
    Texture greenTexture;
    Texture blueTexture;
    Texture blackTexture;
    Texture eraserTexture;
    Texture dessinrecTexture;
    redTexture.loadFromFile("assetocorsa\\boutonrouge.png");
    greenTexture.loadFromFile("assetocorsa\\boutonvert.png");
    blueTexture.loadFromFile("assetocorsa\\boutonbleu.png");
    blackTexture.loadFromFile("assetocorsa\\boutonblack.png");
    eraserTexture.loadFromFile("assetocorsa\\boutoneraser.png");
    
    Sprite redSprite(redTexture);
    redSprite.setPosition(10, 10);

    Sprite greenSprite(greenTexture);
    greenSprite.setPosition(70, 10);

    Sprite blueSprite(blueTexture);
    blueSprite.setPosition(130, 10);

    Sprite blackSprite(blackTexture);
    blackSprite.setPosition(190, 10);

    Sprite eraserSprite(eraserTexture);
    eraserSprite.setPosition(250, 10);

    Sprite dessinrecSprite(dessinrecTexture);
    dessinrecSprite.setPosition(310, 10);

    RectangleShape bg(Vector2f(1920, 50));
    bg.setFillColor(Color(170, 170, 170));

    // Gestion des textes
    Font font;
    if (!font.loadFromFile("assetocorsa\\arial.ttf")) {
        return -1; // Assurez-vous que la police est disponible
    }

    vector<Text> textFields; // Stocke les textes ajoutés
    Text currentText("", font, 20);
    currentText.setFillColor(Color::Black);

    bool selecting = false; // Indique si une zone est en cours de sélection
    Vector2f selectionStart; // Position de départ de la sélection
    RectangleShape selectionBox; // Rectangle pour afficher la zone de sélection
    selectionBox.setFillColor(Color::Transparent);
    selectionBox.setOutlineColor(Color::Black);
    selectionBox.setOutlineThickness(1);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::TextEntered && !currentText.getString().isEmpty()) {
                if (event.text.unicode == '\b' && !currentText.getString().isEmpty()) { // Effacer avec Backspace
                    string str = currentText.getString();
                    str.pop_back();
                    currentText.setString(str);
                }
                else if (event.text.unicode < 128) { // Ajouter caractère ASCII
                    currentText.setString(currentText.getString() + static_cast<char>(event.text.unicode));
                }
            }
        }

        if (Mouse::isButtonPressed(Mouse::Right)) {
            if (!selecting) {
                selecting = true;
                selectionStart = static_cast<Vector2f>(Mouse::getPosition(window));
                selectionBox.setPosition(selectionStart);
                selectionBox.setSize(Vector2f(0, 0));
            }
            else {
                // Met à jour la taille du rectangle
                Vector2f currentPos = static_cast<Vector2f>(Mouse::getPosition(window));
                Vector2f size = currentPos - selectionStart;
                selectionBox.setSize(size);
            }
        }
        else if (selecting && !Mouse::isButtonPressed(Mouse::Right)) {
            // Terminer la sélection
            selecting = false;
            currentText.setPosition(selectionBox.getPosition());
            textFields.push_back(currentText); // Enregistre le texte
            currentText.setString(""); // Réinitialise le texte
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);

            if (redSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                currentColor = Color::Red;
                eraserMode = false;
            }
            else if (greenSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                currentColor = Color::Green;
                eraserMode = false;
            }
            else if (blueSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                currentColor = Color::Blue;
                eraserMode = false;
            }
            else if (blackSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                currentColor = Color::Black;
                eraserMode = false;
            }
            else if (eraserSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                eraserMode = true;
            }
            else {
                CircleShape brush(brushSize);
                brush.setPosition(mousePos.x - brushSize, mousePos.y - brushSize);

                if (eraserMode) {
                    brush.setFillColor(Color::White);
                }
                else {
                    brush.setFillColor(currentColor);
                }
                shapes.push_back(brush);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::C)) shapes.clear();
        if (Keyboard::isKeyPressed(Keyboard::Up)) brushSize = min(50.0f, brushSize + 0.2f);
        if (Keyboard::isKeyPressed(Keyboard::Down)) brushSize = max(1.0f, brushSize - 0.2f);
        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

        window.clear(Color::White);

        for (const auto& shape : shapes) {
            window.draw(shape);
        }

        for (const auto& text : textFields) {
            window.draw(text);
        }

        window.draw(bg);
        window.draw(redSprite);
        window.draw(greenSprite);
        window.draw(blueSprite);
        window.draw(blackSprite);
        window.draw(eraserSprite);
        window.draw(dessinrecSprite);

        if (selecting) {
            window.draw(selectionBox);
        }

        window.display();
    }

    return 0;
}
