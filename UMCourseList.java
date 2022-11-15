import java.util.Map;
import java.util.HashSet;
import java.util.Collection;
import java.util.HashMap;

//this class implements a map
public class UMCourseList {

  private Map<String, Collection<String>> courses;
  
  //constructor
  public UMCourseList() {
	  courses = new HashMap<>();
  }

  //puts a student in acourse
  public void takeCourse(String student, String course)
                throws IllegalArgumentException {
    if (student == null || course == null) {
    	throw new IllegalArgumentException("invalid");
    }
    //checks to make sure the student is not already enrolled in the 
    //course
    if (!isTakingCourse(student,course)) {
    	
    	//if the student is not yet in the map, then adds it as well as 
    	//the course to the map
    	if (!courses.containsKey(student)) {
    		Collection<String> c = new HashSet<String>();
    		c.add(course);
    		courses.put(student, c);
    	}
    	//otherwise, the course is added to the student's collection of courses
    	else if (courses.containsKey(student)) {
    		Collection<String> c = courses.get(student);
    		c.add(course);
    	}
    }
    
  }

  //checks if student is in a course
  public boolean isTakingCourse(String student, String course)
                   throws IllegalArgumentException {
	if (student == null || course == null) {
		throw new IllegalArgumentException("Invalid");
	}
	//if the student is in the map, then the values are checked to see
	//if the course is there
    if (courses.containsKey(student)) {
    	Collection<String> collection = courses.get(student);
    	for (String courseTaking : collection) {
    		if (courseTaking.equals(course)) {
    			return true;
    		}
    	}
    }
    return false;
  }

  //returns the number of courses the student is taking
  public int numCoursesTaking(String student)
               throws IllegalArgumentException {
    if (student == null) {
    	throw new IllegalArgumentException("Invalid");
    }
    //if the student is in the mpa, it counts the number of courses the student
    //is taking
    if (courses.containsKey(student)) {
    	int numCourses = 0;
    	Collection<String> collection = courses.get(student);
    	for (String course: collection) {
    		numCourses++;
    	}
    	return numCourses;
    }
    return 0;
  }

  //checks how many students are enrolled in a particular course
  public int numEnrolled(String course) throws IllegalArgumentException {
    if (course == null) {
    	throw new IllegalArgumentException("invalid");
    }
    //iterates through every course and checks how many students are enrolled
    int numCourses = 0;
    Collection<Collection<String>> collection = courses.values();
    for (Collection<String> courseEnrolled: collection) {
    	for (String courseTaking: courseEnrolled) {
    		if (courseTaking.equals(course)) {
    			numCourses++;
    			}
    		}
    	}
    return numCourses;
  }

  //iterates over every course and finds the course with the most students
  //enrolled in it
  public String mostPopularCourse() {
    String popCourse = "";
    int enrolledNum = 0;
    for (String key : courses.keySet()) {
    	Collection<String> collection = courses.get(key);
    	for (String course : collection) {
    		if (numEnrolled(course) > enrolledNum) {
    			popCourse = course;
    			enrolledNum = numEnrolled(course);
    		}
    	}
    }
    if (enrolledNum == 0) {
    	return null;
    }
    return popCourse;
  }

  //finds the course and then removes the course from the collection
  //of values if the student is taking it
  public boolean dropCourse(String student, String course)
                   throws IllegalArgumentException {
    if (student == null || course == null) {
    	throw new IllegalArgumentException("invalid");
    }
    if (isTakingCourse(student, course)) {
    	Collection<String> values = courses.get(student);
    	for (String val : values) {
    		if (val.equals(course)) {
    			values.remove(course);
    			return true;
    		}
    	}
    }
    return false;
  }

}
