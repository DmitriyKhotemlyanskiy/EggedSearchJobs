package equiv;

import java.util.*;


public class Equiv<E> {
	private List<LinkedList<E>> list;		//List for saving groups
	private int counter;					//counter for saving the amount of the groups
	
	public Equiv(){
		list = null;
		counter = 0;
	}
	
	public void add(E e1, E e2) {
		if(list==null) {
			list = new LinkedList<LinkedList<E>>();		//Create LinkedList<E>
			list.add(new LinkedList<E>());		//Create LinkedList<E> into the list
			list.get(counter).add(e1);		//add a new Item to list(0)->LinkedList
			list.get(counter).add(e2);		//add a new Item to list(0)->LinkedList
		}
		if(hasItem(e1)==-1&&hasItem(e2)==-1) {		//If we have not group with this 
			counter++;								//Items we create a new group for them
			list.add(new LinkedList<E>());			//and adds to it group
			list.get(counter).add(e1);
			list.get(counter).add(e2);
		}
		if(hasItem(e1)==-1&&hasItem(e2)!=-1) {		//If we have one of these Items in some group
			list.get(hasItem(e2)).add(e1);			//we add another item in this group
		}
		else
			list.get(hasItem(e1)).add(e2);
	}
	
	public boolean are(E e1, E e2) {
		if(hasItem(e1)==hasItem(e2))
			return true;
		return false;
	}
	
	private int hasItem (E e) {				//Checking if e contains in some of group
		int inLinkedList;						//if yes-> returns number of a group
		for(int i=0;i<list.size();i++) {		// if not-> returns -1
			for(int j=0;j<list.get(i).size();j++) {
				if(e == list.get(i).get(j)) {
					inLinkedList = i;
					return inLinkedList;
				}
			}
		}
		inLinkedList =-1;
		return inLinkedList;
	}
}
