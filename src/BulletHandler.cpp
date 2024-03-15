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
    pPlayerBullet ->load(new LoaderParams(x, y, width, height, textureID, numFrames), heading);
    m_playerBullets.push_back(pPlayerBullet);
}

void BulletHandler::addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames,
                                   Vector2D heading) {
    EnemyBullet* pEnemyBullet = new EnemyBullet();
    pEnemyBullet ->load(new LoaderParams(x, y, width, height, textureID, numFrames), heading);
    m_playerBullets.push_back(pEnemyBullet);
}

void BulletHandler::updateBullets() {
    for (auto p_it = m_playerBullets.begin();
         p_it != m_playerBullets.end();) {
        if((*p_it)->getPosition().getX() < 0
           || (*p_it)->getPosition().getX() > Game::Instance()->getGameWidth()
           || (*p_it)->getPosition().getY() < 0
           || (*p_it)->getPosition().getY() > Game::Instance()->getGameHeight()
           || (*p_it)->dead()) {
            //delete * p_it;
            p_it = m_playerBullets.erase(p_it);
        } else {
            (*p_it)->update();
            ++p_it;
        }
    }

    for (auto e_it = m_enemyBullets.begin();
         e_it != m_enemyBullets.end();) {
        if((*e_it)->getPosition().getX() < 0
           || (*e_it)->getPosition().getX() > Game::Instance()->getGameWidth()
           || (*e_it)->getPosition().getY() < 0
           || (*e_it)->getPosition().getY() > Game::Instance()->getGameHeight()
           || (*e_it)->dead()) {
            //delete * e_it;
            e_it = m_enemyBullets.erase(e_it);
        } else {
            (*e_it)->update();
            ++e_it;
        }
    }
}

const std::vector<EnemyBullet*> BulletHandler::getEnemyBullets() {
    return std::vector<EnemyBullet*>();
}

const std::vector<PlayerBullet*> BulletHandler::getPlayerBullets() {
    return std::vector<PlayerBullet*>();
}

void BulletHandler::drawBullets() {
    for (unsigned int p = 0; p < m_playerBullets.size(); p++) {
        m_playerBullets[p]->draw();
    }

    for (unsigned int e = 0; e < m_enemyBullets.size(); e++) {
        m_enemyBullets[e]->draw();
    }
}


void BulletHandler::clearBullets() {
    m_enemyBullets.clear();
    m_playerBullets.clear();
}