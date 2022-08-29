#ifndef _TRACK
#define _TRACK

#include <thread>
#include <vector>

#define N_MAX_TRACK 20

namespace Q {
	enum {VERTICAL = 0, HORIZONTAL = 1, ME_GAMER, VIRTUAL_GAMER, ONLINE_GAMER};
}

template <typename T>
class Track {

	protected:

		struct List {
			std::vector <T> vArray_trk;
			List* next = nullptr;
			int nbr_succeed = 0;

			~List() {
				vArray_trk.clear();
				std::cout << "\n   delete list: "<<next<<std::endl;
				delete next;
				next = nullptr;
			}

		};

		std::vector <T> vArrayCells;
		int nbr_succeed = 0;

	private:

		bool  *ptr_Direction = nullptr;
		short *ptr_Lines     = nullptr;
		short *ptr_Columns   = nullptr;

		std::vector <List*> vArrayList_V;
		std::vector <List*> vArrayList_H;

		void continuous(T x, List* ptr_list = nullptr) {

			if(ptr_list->next == nullptr) {
				ptr_list->nbr_succeed ++;
				vArrayCells.push_back(x);
				return;
			}

			if(*ptr_Direction == Q::VERTICAL) {
				for(const auto& y : ptr_list->next->vArray_trk)
					if(x - *ptr_Columns == y) {

						vArrayCells.push_back(x); 
						continuous(y, ptr_list->next);
						return;

					}

				for(auto& y : ptr_list->vArray_trk)
					if(x - 1 == y || x + 1 == y) {

						T yy = y;
						y = 0;
						continuous(yy, ptr_list);
						y = yy;
					}
			}


			if(*ptr_Direction == Q::HORIZONTAL) {
				for(const auto& y : ptr_list->next->vArray_trk)
					if(x - 1 == y) {

						vArrayCells.push_back(x);
						continuous(y, ptr_list->next);
						return;

					}

				for(auto& y : ptr_list->vArray_trk)
					if(x - *ptr_Columns == y || x + *ptr_Columns == y) {

						T yy = y;
						y = 0;
						continuous(yy, ptr_list);
						y = yy;
					}
			}

		}



		void run_tracking(List* ptr_list) {
			for(const auto& x : ptr_list->vArray_trk)
				continuous(x, ptr_list);
		};

		void start() {

			if(!vArrayCells.empty())
				vArrayCells.clear();

			if(*ptr_Direction == Q::VERTICAL) {
				run_tracking (vArrayList_V.back());
				nbr_succeed = vArrayList_V[0]->nbr_succeed;
			}

			else if(*ptr_Direction == Q::HORIZONTAL) {
				run_tracking (vArrayList_H.back());	
				nbr_succeed = vArrayList_H[0]->nbr_succeed;
			}

			for(const auto& n : vArrayCells)
				std::cout <<"  "<< n <<"  ";

			if(*ptr_Direction == Q::VERTICAL)
				std::cout <<"\n\n   succeed n : " << nbr_succeed << std::endl<<std::endl;  

			if(*ptr_Direction == Q::HORIZONTAL)
				std::cout <<"\n\n   succeed n : " << nbr_succeed << std::endl<<std::endl;  

		}

		void tracking(std::vector <T> *ptr_vtab = nullptr, short *ptr_lines = nullptr, short *ptr_columns = nullptr, bool *ptr_direction = nullptr) {

			if(ptr_vtab == nullptr || ptr_lines == nullptr || ptr_columns == nullptr || ptr_direction == nullptr)
				return;

			if(ptr_vtab->empty())
				return;

			std::vector <T> *ptr_vtab_trk = ptr_vtab;
			ptr_Lines                     = ptr_lines;
			ptr_Columns                   = ptr_columns;
			ptr_Direction                 = ptr_direction;

			List *curr_list_ptr = nullptr; /// *last->next = nullptr 

			if(*ptr_Direction == Q::VERTICAL)
				for (int j = 1; j <= *ptr_Lines; j++) {
					List *list_ptr = new List;
					list_ptr->next = curr_list_ptr;
					curr_list_ptr  = list_ptr;

					for (int k = 1; k <= *ptr_Columns; k++)
						for (const auto& n : *ptr_vtab_trk)
							if ((1 + (j - 1) * (*ptr_Columns)) + (k - 1) * 1  == n)
								list_ptr->vArray_trk.push_back(n);
					vArrayList_V.push_back(list_ptr);
				}

			else if(*ptr_Direction == Q::HORIZONTAL)
				for (int k = 1; k <= *ptr_Columns; k++) {
					List *list_ptr = new List;
					list_ptr->next = curr_list_ptr;
					curr_list_ptr  = list_ptr;

					for (int j = 1; j <= *ptr_Lines; j++)
						for (const auto& n : *ptr_vtab_trk)
							if ((1 + (k - 1) * 1) + (j - 1) * (*ptr_Columns)  == n)
								list_ptr->vArray_trk.push_back(n);
					vArrayList_H.push_back(list_ptr);
				}


			if(*ptr_Direction == Q::VERTICAL) {
				std::cout << "\n VERTICAL\n";
				flush(vArrayList_V.back());
			}

			if(*ptr_Direction == Q::HORIZONTAL) {
				std::cout << "\n HORIZONTAL\n";  
				flush(vArrayList_H.back());  
			}

			start();

			return;
		};

		void flush(List* pL) {	
			if(pL == nullptr)
				return;
			for(auto n : pL->vArray_trk) 
				std::cout << "  "<< n;
			std::cout<<std::endl;
			flush(pL->next);
		}

	protected:

		void track_Process(std::vector <T> *ptr_vtab, short *ptr_lines, short *ptr_columns, bool *ptr_direction) {

			if(ptr_vtab == nullptr || ptr_lines == nullptr || ptr_columns == nullptr || ptr_direction == nullptr)
				return;
			this->tracking(ptr_vtab, ptr_lines, ptr_columns, ptr_direction);

		};

		void terminate_Process() {

			if(!vArrayList_V.empty()) {
				delete vArrayList_V.back();
				vArrayList_V.back() == nullptr;
			}

			if(!vArrayList_H.empty()) {
				delete vArrayList_H.back();
				vArrayList_H.back() == nullptr;
			}

			vArrayList_V.clear();
			vArrayList_H.clear();

			std::cout 
				<< " ... tracking is closed ... R: "
				<< vArrayList_V.size() + vArrayList_H.size() << std::endl;
		};


		Track() {
			terminate_Process();
		};

		~Track() {}
};

#endif













