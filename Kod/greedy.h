struct greedy{
  //  int tile_distance[]; //tabell med avståndet mellan alla nod-par
  // int total_area[];  //total_area={totalt antal områden,r1,k1, r2,k2,...}, område1=(r1,k1)
  // struct Node node_matrix; //B[][]
  int Break[2]; //brytvillkor för algoritm{nuvarande värde, givet brytvillkor}
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
