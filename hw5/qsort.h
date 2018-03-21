#include <vector>

	//swapping two elements in the vector with indexes as parameters
  	template<class T>
  	void swap(std::vector<T> &myArray, int first, int second)
  	{
  		int temp = myArray[first];
  		myArray[first] = myArray[second];
  		myArray[second] = temp;
  	}

  	//Finding the median
  	template <class T>	
  	int findMedian(std::vector<T> &myArray, int first, int last)
  	{
  		int middle = (first+last)/2;

  		//when the first is the median
  		if(myArray[first]>=myArray[middle] && myArray[first]<=myArray[last])
  		{
  			return first;
  		}

  		else if(myArray[first]>=myArray[last] && myArray[first]<=myArray[middle])
  		{
  			return first;
  		}

  		//when the middle is the median
  		else if(myArray[middle]>=myArray[first] && myArray[middle]<=myArray[last])
  		{
  			return middle;
  		}

  		else if(myArray[middle]>=myArray[last] && myArray[middle]<=myArray[first])
  		{
  			return middle;
  		}

  		//when the last is the median
  		else if(myArray[last]>=myArray[middle] && myArray[last]<=myArray[first])
  		{
  			return last;
  		}

  		else if(myArray[last]>=myArray[first] && myArray[last]<=myArray[middle])
  		{
  			return last;
  		}

      return middle;
  	}

  	//Partitioning the vector
  	//Pushes the median value to the end
  	//Then, do the partition
  	template <class T,class Comparator>
  	int partition(std::vector<T> &myArray, int start, int end, Comparator comp)
  	{
  		int pivot = findMedian(myArray,start,end);
  		swap(myArray,pivot,end);

  		int pivotvalue = myArray[end];
  		int pivotindex = start;

  		for (int i=start; i<end; i++)
  		{
  			if(comp(myArray[i],pivotvalue))
  			{
  				swap(myArray,i,pivotindex);
  				pivotindex++;
  			}
  		}

  		swap(myArray,pivotindex,end);
  		return pivotindex;
  	}

  	//Recursive call to quicksort
	template <class T, class Comparator>
  	void quicksort(std::vector<T> &myArray, int start, int end, Comparator comp)
  	{
  		if(start < end)
  		{
  			int loc = partition(myArray, start, end, comp);
  			quicksort(myArray, start, loc-1, comp);
  			quicksort(myArray, loc+1, end, comp);
  		}
  	}

	//Original Quicksort given by the problem
	template <class T, class Comparator>
  	void QuickSort (std::vector<T> &myArray, Comparator comp)
  	{
  		int start = 0;
  		int end = static_cast<int>(myArray.size()-1); 
  		quicksort(myArray,start,end,comp);
  	}