/**
* SortedList interface for use with the CM10228: Principles of Programming 2 coursework.
*
* This should not be modified by the student.
*
* @author		Christopher Clarke
* @version		1.0
*/
public interface SortedList {

	/**
	* Returns the number of Nodes in the linked list.
	*
	* @return      the number of Nodes in the linked list
	*/
	public int size();

	/**
	* Adds a Node with the specified string to the linked list in
	* the appropriate position given the specified alphabetical order
	* (i.e., ascending/descending).
	*
	* @param  string  a String to be added to the linked list
	*/
	public void add(String string);

	/**
	* Adds a Node to the linked list in the appropriate position
	* given the specified alphabetical order (i.e., ascending/descending).
	*
	* @param  node  a Node to be added to the linked list
	*/
	public void add(Node node);

	/**
	* Returns the first Node of the linked list given the specified
	* alphabetical order (i.e., ascending/descending).
	*
	* @return      the first Node in the linked list
	*/
	public Node getFirst();

	/**
	* Returns the last Node of the linked list given the specified
	* alphabetical order (i.e., ascending/descending).
	*
	* @return      the last Node in the linked list
	*/
	public Node getLast();

	/**
	* Returns the Node at the specified index assuming indices start
	* at 0 and end with size-1 given the specified alphabetical order
	* (i.e., ascending/descending).
	*
	* @param  index  the index of the Node in the linked list to be retrieved
	* @return      the Node in the linked list at the specified index
	*/
	public Node get(int index);

	/**
	* Checks to see if the list contains a Node with the specified
	* string.
	*
	* @param  string  the String to be searched for in the linked list
	* @return       True if the string is present or false if not
	*/
	public boolean isPresent(String string);

	/**
	* Removes the first Node from the list given the specified
	* alphabetical order (i.e., ascending/descending).
	*
	* @return      Returns true if successful or false if unsuccessful
	*/
	public boolean removeFirst();

	/**
	* Removes the last Node from the list given the specified
	* alphabetical order (i.e., ascending/descending).
	*
	* @return      Returns true if successful or false if unsuccessful
	*/
	public boolean removeLast();

	/**
	* Removes the Node at the specified index from the list assuming indices
	* start at 0 and end with size-1 given the specified alphabetical order
	* (i.e., ascending/descending)
	*
	* @param  index  the index of the Node in the linked list to be removed
	* @return      Returns true if successful or false if unsuccessful
	*/
	public boolean remove(int index);

	/**
	* Removes the Node from the list that contains the specified string.
	*
	* @param  string  the string to be removed from the linked list
	* @return      Returns true if successful or false if unsuccessful
	*/
	public boolean remove(String string);

	/**
	* Orders the linked list in ascending alphabetical order.
	*
	*/
	public void orderAscending();

	/**
	* Orders the linked list in descending alphabetical order.
	*
	*/
	public void orderDescending();

	/**
	* Prints the contents of the linked list in the specified alphabetical order
	* (i.e., ascending/descending) to System.out with each node's string on
	* a new line.
	*
	*/
	public void print();
}


class SortedLinkedList implements SortedList {
	private Node head;

	public int size() {
		int size = 0;
		for (Node node = head; node != null; node = node.getNext()) {
			size++;
		}
		return size;
	}

	public void add(String string) {
		Node prevNode = null;
		Node currentNode = head;

		boolean insert = false;

		if (this.isPresent(string)) {
			return;
		}

		loop: {
			while (!insert) {
				if (currentNode == null) {
					insert = true;
					break;
				}
				String nodeString = currentNode.getString().toUpperCase();
				String upperString = string.toUpperCase();


				// check if string is less than nodeString
				for (int i = 0; i < nodeString.length() && i < upperString.length() ; i++) {
					char addChar = upperString.charAt(i);
					char nodeChar = nodeString.charAt(i);
					if (addChar < nodeChar) {
						insert = true;
						break loop;
					} else if (addChar > nodeChar) {
						break;
					}
				}

				prevNode = currentNode;
				currentNode = currentNode.getNext();
			}
		}

		if (insert) {
			Node newNode = new Node(string);

			// check if the new node is the head
			if (currentNode == head) {
				head = newNode;
			}

			// set the next and prev nodes
			if (currentNode != null) {
				currentNode.setPrev(newNode);
				newNode.setNext(currentNode);
			}
			
			newNode.setPrev(prevNode); // set the prev node

			// set the prev node's next node
			if (prevNode != null) {
				prevNode.setNext(newNode);
			}
		}
		
	}

	public void add(Node node) {
		Node prevNode = null;
		Node currentNode = head;

		boolean insert = false;

		if (this.isPresent(node.getString())) {
			return;
		}

		String string = node.getString();
		loop: {
			while (!insert) {
				if (currentNode == null) {
					insert = true;
					break;
				}

				String nodeString = currentNode.getString().toUpperCase();
				String upperString = string.toUpperCase();


				// check if string is less than nodeString
				for (int i = 0; i < nodeString.length() && i < upperString.length() ; i++) {
					char addChar = upperString.charAt(i);
					char nodeChar = nodeString.charAt(i);
					if (addChar < nodeChar) {
						insert = true;
						break loop;
					} else if (addChar > nodeChar) {
						break;
					}
				}

				prevNode = currentNode;
				currentNode = currentNode.getNext();
			}
		}

		if (insert) {
			Node newNode = node;

			// check if the new node is the head
			if (currentNode == head) {
				head = newNode;
			}

			// set the next and prev nodes
			if (currentNode != null) {
				currentNode.setPrev(newNode);
				newNode.setNext(currentNode);
			}
			
			newNode.setPrev(prevNode); // set the prev node

			// set the prev node's next node
			if (prevNode != null) {
				prevNode.setNext(newNode);
			}
		}
	}

	public Node getFirst() {
		return head;
	}

	public Node getLast() {
		for (Node node = head; node != null; node = node.getNext()) {
			if (node.getNext() == null) {
				return node;
			}
		}
		return null;
	}

	public Node get(int index) {
		int i = 0;
		for (Node node = head; node != null; node = node.getNext()) {
			if (i == index) {
				return node;
			}
			i++;
		}
		return null;
	}

	public boolean isPresent(String string) {
		string = string.toUpperCase();
		for (Node node = head; node != null; node = node.getNext()) {
			String nodeString = node.getString().toUpperCase();
			if (string.equals(nodeString)) {
				return true;
			}
		}
		return false;
	}

	public boolean removeFirst() {
		if (head != null) {
			head = head.getNext();
			return true;
		}
		return false;
	}

	public boolean removeLast() {
		Node prevNode = null;
		for (Node node = head; node != null; node = node.getNext()) {
			prevNode = node;
		}

		if (prevNode != null && prevNode.getPrev() != null) {
			prevNode.getPrev().setNext(null);
			return true;
		}

		if (this.size() == 1) {
			head = null;
			return true;
		}
		return false;
	}

	public boolean remove(int index) {
		int i = 0;
		for (Node node = head; node != null; node = node.getNext()) {
			if (i == index) {
				Node prevNode = node.getPrev();
				Node nextNode = node.getNext();

				if (prevNode != null) {
					prevNode.setNext(nextNode);
				} else {
					head = nextNode;
				}

				if (nextNode != null) {
					nextNode.setPrev(prevNode);
				}
				return true;
			}
			i++;
		}
		return false;
	}

	public boolean remove(String string) {
		string = string.toUpperCase();
		for (Node node = head; node != null; node = node.getNext()) {
			String nodeString = node.getString().toUpperCase();
			if (string.equals(nodeString)) {
				Node prevNode = node.getPrev();
				Node nextNode = node.getNext();

				if (prevNode != null) {
					prevNode.setNext(nextNode);
				} else {
					head = nextNode;
				}

				if (nextNode != null) {
					nextNode.setPrev(prevNode);
				}
				return true;
			}
		}

		return false;
	}

	public void orderAscending() {
		Node current = head;
		Node next;

		while (current != null) {
			next = current.getNext();

			String temp = current.getString();
			
			this.remove(current.getString());
			this.add(temp);

			current = next;
		}
	}

	public void orderDescending() {
		this.orderAscending();
		
		Node prev = null;
		Node current = head;
		Node next;

		while (current != null) {
			next = current.getNext();

			current.setNext(prev);
			current.setPrev(next);

			prev = current;
			current = next;
		}

		head = prev;
	}

	public void print() {
		for (Node node = head; node != null; node = node.getNext()) {
			System.out.println(node.getString());
		}
	}
}