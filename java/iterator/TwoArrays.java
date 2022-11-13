package iterator;

import java.util.Iterator;

public class TwoArrays implements Iterable<Integer> {
	private int[] a3;
	private int maxLen;

	public TwoArrays(int[] a1, int[] a2) {
		int i = 0;
		int j = 0;
		maxLen = a1.length+a2.length;
		a3 = new int[maxLen];
		while(i<maxLen) {
			if(j<a1.length&&j<a2.length) {
				a3[i] = a1[j];
				a3[i+1] = a2[j];
				i+=2;
				j++;
			}
			else if(j<a1.length&&j>=a2.length) {
				a3[i] = a1[j];
				i++;
				j++;
			}
			else if(j>=a1.length&& j<a2.length) {
				a3[i] = a2[j];
				i++;
				j++;
			}
				
		}
	}

	@Override
	public Iterator<Integer> iterator() {
		return new Iterator<Integer>() {
			int i = 0;

			@Override
			public boolean hasNext() {
				return i < a3.length;
			}

			@Override
			public Integer next() {
				if (!hasNext())
					throw new ArrayIndexOutOfBoundsException();
				else
					return a3[i++];
			}

		};
	}

}
