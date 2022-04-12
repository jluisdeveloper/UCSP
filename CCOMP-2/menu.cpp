
	CLinkedList<int, CLess<int>> test;
	int option, n;
	while(true){
		cout << " |++++++++ Binary Tree +++++++++| " <<endl;
		cout << " |+++++Press (1) to Insert +++++| " <<endl;
		cout << " |+++++Press (2) to Remove +++++| " <<endl;
		cout << " |++Press (3) to PrintReverse ++| " <<endl;
		cout << " |+++++Press (0) to Quit +++++++| " <<endl;
		cout << " |++++++++++++++++++++++++++++++| " <<endl;
		cout << "  * option: " ;
		cin>>option;
		if(option==1){
			while(true){
			cout << "\n 0 para volver, ingrese un numero: " ;
			cin >> n;
			if(n==0)
				break;
			test.insert(n);
			test.print();
			}
		}else if(option==2){
			cout << "\n 0 para volver, BORRAR el numero: ";
			cin >> n;
			test.remove(n);
			//test.~CLinkedList();
			test.print();
		}else if(option==3){
			cout << "\nLista circular en REVERSA" << endl;
			test.print_reversed();
		}else if(option==0)
			break;
	}