            int cidade1, cidade2;
            do
            {
                cidade1 = rand() % grafo.numVertices;
                cidade2 = rand() % grafo.numVertices;
            } while ((cidade1 == 0) || (cidade2 == 0) || (cidade1 == cidade2));