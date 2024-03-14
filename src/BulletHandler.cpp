#include "BulletHandler.h"

BulletHandler* BulletHandler::s_pInstance = new BulletHandler();

BulletHandler::BulletHandler() {}

BulletHandler* BulletHandler::Instance() {
    if(s_pInstance == 0) {
        s_pInstance = new BulletHandler();
        return s_pInstance;
    }
    return s_pInstance;
}


void BulletHandler::addPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames,
                                    Vector2D heading) {
    PlayerBullet* pPlayerBullet = new PlayerBullet();
    pPlayerBullet ->load(std::unique_ptr<LoaderParams> (new LoaderParams(x, y, width, height, textureID, numFrames)), heading);
    m_playerBullets.push_back(pPlayerBullet);
}

void BulletHandler::addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames,
                                   Vector2D heading) {
    EnemyBullet* pEnemyBullet = new EnemyBullet();
    pEnemyBullet ->load(std::unique_ptr<LoaderParams> (new LoaderParams(x, y, width, height, textureID, numFrames)), heading);
    m_playerBullets.push_back(pEnemyBullet);
}

void BulletHandler::updateBullets() {
    for (std::vector<PlayerBullet*>::iterator p_it = m_playerBullets.begin(); p_it != m_playerBullets.end();){
        if ((*p_it) -> getPosition().getX() < 0 || (*p_it) -> getPosition().getX() > Game::Instance() -> getGameWidth() || (*p_it) -> getPosition().getY() < 0 || (*p_it) -> getPosition().getY() > Game::Instance() ->getGameHeight() || (*p_it) -> dead()) {
            delete *p_it;
            p_it = m_playerBullets.erase(p_it);
        } else {
            (*p_it) -> update();
            ++p_it;
        }
    }
}