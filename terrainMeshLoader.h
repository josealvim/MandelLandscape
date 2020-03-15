#ifndef MANDELLANDSCAPE_TERRAINMESHLOADER_H
#define MANDELLANDSCAPE_TERRAINMESHLOADER_H

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <complex>

#include <GL/glew.h>

#include "math3d.h"

class
TerrainMeshLoader
{
public:
    TerrainMeshLoader();
    ~TerrainMeshLoader();

    const std::vector<Vector3f>&
    updateMeshPoints(double, double, double);

    std::vector<GLuint>
    getMeshIndices();

    static double
    heightAt(const std::complex<double>&);
    static constexpr int granularity = 400;
    static constexpr int iterations = 100;
    GLuint m_VBO;
    GLuint m_loadingVBO;
private:
    std::thread m_worker;
    std::mutex m_loadMutex;
    std::condition_variable m_loadCond;
    bool m_readyToLoad = false;
    bool m_readyToSwap = false;
    bool m_destruct = false;
    bool m_doneLoading = false;
    unsigned int m_loadIndex = 0;

    double m_x;
    double m_z; 
    double m_scale;
    
    std::shared_ptr<std::vector<Vector3f>> m_currentMeshPoints;
    std::shared_ptr<std::vector<Vector3f>> m_loadingMeshPoints;

    void meshLoading();
};


#endif
