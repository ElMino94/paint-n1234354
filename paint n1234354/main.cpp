#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

int main() {

    RenderWindow window(VideoMode(1920, 1080), "Paint pour les nuls");
    window.setFramerateLimit(9999999999999999999);

    RenderTexture renderTexture;
    renderTexture.create(1920, 1080);
    renderTexture.clear(Color::White);

    vector<CircleShape> shapes;

    Color currentColor = Color::Black;
    float brushSize = 5.0f;
    bool eraserMode = false;

    Texture redTexture;
    Texture greenTexture;
    Texture blueTexture;
    Texture blackTexture;
    Texture eraserTexture;
    Texture saveTexture;
    redTexture.loadFromFile("assetocorsa\\boutonrouge.png");
    greenTexture.loadFromFile("assetocorsa\\boutonvert.png");
    blueTexture.loadFromFile("assetocorsa\\boutonbleu.png");
    blackTexture.loadFromFile("assetocorsa\\boutonblack.png");
    eraserTexture.loadFromFile("assetocorsa\\boutoneraser.png");
    saveTexture.loadFromFile("assetocorsa\\boutonsave.png");

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

    Sprite saveSprite(saveTexture);
    saveSprite.setPosition(1800, 10);

    RectangleShape bg(Vector2f(1920, 50));
    bg.setFillColor(Color(170, 170, 170));


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
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
            else if (saveSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                renderTexture.display();
                renderTexture.getTexture().copyToImage().saveToFile("dessin.png");
                printf("Une image a ete sauvegardee\n");
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

                if (eraserMode) {
                    brush.setFillColor(Color::White);
                }
                else {
                    brush.setFillColor(currentColor);
                }

                shapes.push_back(brush);

                renderTexture.draw(brush);
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

        window.draw(bg);
        window.draw(redSprite);
        window.draw(greenSprite);
        window.draw(blueSprite);
        window.draw(blackSprite);
        window.draw(eraserSprite);
        window.draw(saveSprite);
        window.display();
    }


    return 0;
}