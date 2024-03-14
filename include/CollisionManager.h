#ifndef PLATFORMER_COLLISIONMANAGER_H
#define PLATFORMER_COLLISIONMANAGER_H

class GameObject;
class TileLayer;
class Player;

class CollisionManager {
public:
    const static int s_buffer;

    static bool RectRect(SDL_Rect *A, SDL_Rect *B);
    void checkPlayerEnemyBulletCollision(Player* pPlayer);
    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*> &objects);
    void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*> &collistionLayers);
};

#endif //PLATFORMER_COLLISIONMANAGER_H
