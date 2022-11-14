#pragma once
#include <memory>
#include <thread>

namespace ag {
class IGraphicsDriver;
class Looper;
/**
 * @brief Engine class is ag Engine.
 */
class Engine {
public:
    using Instance = std::shared_ptr<Engine>;

    ~Engine();
    /**
     * @brief Get the Engine object
     * @return Instance
     */
    static Instance getInstance();

    /**
     * @brief throw exception if instance not exist.
     */
    static void require();

    /**
     * @brief startup a ag Engine.
     * @param argc
     * @param argv
     */
    Instance startup(int argc, char* argv[]);

    /**
     * @brief shutdown a ag Engine.
     */
    void shutdown();

    /**
     * @brief Get the Looper object
     * @return std::shared_ptr<Looper>
     */
    std::shared_ptr<Looper> getLooper() const;

    /**
     * @brief Get the Graphics Driver object
     * @return std::shared_ptr<IGraphicsDriver>
     */
    std::shared_ptr<IGraphicsDriver> getGraphicsDriver() const;

private:
    static std::mutex s_mutex;
    static Instance s_instance;
    bool m_started;
    std::shared_ptr<Looper> m_looper;
    std::shared_ptr<IGraphicsDriver> m_graphicsDriver;
    Engine();
};
}