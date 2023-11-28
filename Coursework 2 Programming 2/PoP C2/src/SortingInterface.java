/**
* Sorting interface for use with the CM10228: Principles of Programming 2 coursework.
*
* This should not be modified by the student.
*
* @author		Christopher Clarke
* @version		1.0
*/
import java.util.ArrayList;

public interface SortingInterface {

	/**
	* Sets and sorts the values provided in ascending order.
	*
	* @param  values		the values to be sorted
	*/
	public void setValues(ArrayList<Double> values);

	/**
	* Returns the gaps used by the sorting algorithm.
	*
	* @return       The gaps used by the sorting algorithm to sort the ArrayList
	*/
	public ArrayList<Integer> getGaps();

	/**
	* Adds a value to the sorted ArrayList in ascending order.
	*
	* @param  value		the double to be added to the array list
	*/
	public void add(Double value);

	/**
	* Removes a value at the specified index from the sorted ArrayList.
	*
	* @param  index			the index of the double to be removed
	*/
	public void remove(int index);

	/**
	* Sorts the ArrayList in ascending order.
	*
	*/
	public void sort();
}


class CustomSort implements SortingInterface {

	public ArrayList<Double> values = new ArrayList<Double>();
	public ArrayList<Integer> gaps = new ArrayList<Integer>();

	public void setValues(ArrayList<Double> values) {
		this.values = values;
		this.sort();
	}

	public ArrayList<Integer> getGaps() {
		ArrayList<Integer> temp = new ArrayList<>();
    	ArrayList<Integer> gaps = new ArrayList<>();

		int n = values.size();
		int gap = 1, i = 2;

		while(gap < n) {
			temp.add(gap);
			gap = (int) (Math.pow(2, i) - 1);
			i++;
		}

		for(i = temp.size() - 1; i >= 0; i--) {
			gaps.add(temp.get(i));
		}

		return gaps;
	}

	public void add(Double value) {
		values.add(value);
	}

	public void remove(int index) {
		values.remove(index);
	}

	public void sort() {
		int n = this.values.size();
		this.gaps = getGaps();
		for (Integer gap : this.gaps) {
			for(int i = gap; i < n; i++) {
				Double temp = this.values.get(i);
				int j = 0;
				for (j = i; j >= gap ; j -= gap) {
					if (this.values.get(j - gap) <= temp) {
						break;
					}
					this.values.set(j, values.get((int) (j - gap)));
				}
				this.values.set(j, temp);
			}
		}
	}
}