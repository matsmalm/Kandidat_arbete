struct greedy{
  //  int tile_distance[]; //tabell med avst�ndet mellan alla nod-par
  // int total_area[];  //total_area={totalt antal omr�den,r1,k1, r2,k2,...}, omr�de1=(r1,k1)
  // struct Node node_matrix; //B[][]
  int Break[2]; //brytvillkor f�r algoritm{nuvarande v�rde, givet brytvillkor}
  // int solution[]; //solution= {antal jagare,antal steg, sj1r1,sj1k1,..., sj1r2,sj1k2,...}
};
struct greedy preGreedy(); /*
arguments are: Node Matrix, {Pursuers, start paths}, BREAK. 
Break condition is integer for runtime before termination.
*/
void greedyAlg(); /*
arguments are: Node Matrix, {Pursuers, start paths}, BREAK. 
Break condition is integer for runtime before termination.
*/
