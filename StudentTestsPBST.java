import org.junit.*;
import static org.junit.Assert.*;
import pbst.PBST;
import pbst.EmptyPBST;
import pbst.EmptyPBSTException;

public class StudentTests {

	//checks that everything is added correctly for nonEmpty and Empty PBST
	@Test public void testStudent1() {
		assertEquals("",EmptyPBST.getInstance().toString());
		assertEquals(EmptyPBST.getInstance().numPairs(),0);
		assertEquals(TestData.sampleTree2().toString(), "1/e 2/l 3/e 5/p 7/h "
				+ "11/a 13/n 17/t ");
		assertEquals(TestData.sampleTree2().numPairs(), 8);
	}
	
	//removes all elements from tree and tests to see that everything
	//is removed correctly and that numPairs() is correct after deletions
	//also checks that the objects are correctly placed by utilizing 
	//pathToBalance()
	@Test public void studentTest2() {
		PBST<Integer, Character> tree= TestData.sampleTree2();
	    
	    assertEquals(tree.pathBalance(1),-2);
	    tree= tree.removeKeyValuePair(1);
		assertEquals(tree.toString(), "2/l 3/e 5/p 7/h "
				+ "11/a 13/n 17/t ");
		assertEquals(tree.pathBalance(2),-2);
		assertEquals(tree.pathBalance(3),-1);
		
		tree = tree.removeKeyValuePair(2);
		assertEquals(tree.toString(), "3/e 5/p 7/h "
				+ "11/a 13/n 17/t ");
		assertEquals(tree.pathBalance(3),-2);
		
		tree = tree.removeKeyValuePair(3);
		assertEquals(tree.toString(), "5/p 7/h "
				+ "11/a 13/n 17/t ");
		assertEquals(tree.pathBalance(5),-1);
		
		tree = tree.removeKeyValuePair(5);
		assertEquals(tree.toString(), "7/h "
				+ "11/a 13/n 17/t ");
		assertEquals(tree.numPairs(), 4);
		assertEquals(tree.pathBalance(7),0);
		
		tree = tree.removeKeyValuePair(7);
		assertEquals(tree.toString(), "11/a 13/n 17/t ");
		assertEquals(tree.numPairs(), 3);
		assertEquals(tree.pathBalance(11),0);
		
		tree = tree.removeKeyValuePair(11);
		assertEquals(tree.toString(), "13/n 17/t ");
		assertEquals(tree.numPairs(), 2);
		assertEquals(tree.pathBalance(13),0);
		
		tree = tree.removeKeyValuePair(13);
		assertEquals(tree.toString(), "17/t ");
		assertEquals(tree.numPairs(), 1);
		assertEquals(tree.pathBalance(17),0);
		
		tree = tree.removeKeyValuePair(17);
		assertEquals(tree.toString(), "");
		assertEquals(tree.numPairs(), 0);
		
	}
	
	//tests getValueByKey() for empty and nonempty PBST
	@Test public void studentTest3() {
		assertEquals(Character.valueOf('l'), 
				TestData.sampleTree2().getValueByKey(2));
		assertEquals(Character.valueOf('e'), 
				TestData.sampleTree2().getValueByKey(3));
		assertEquals(Character.valueOf('p'), 
				TestData.sampleTree2().getValueByKey(5));
		assertEquals(Character.valueOf('t'), 
				TestData.sampleTree2().getValueByKey(17));
		assertEquals(Character.valueOf('h'), 
				TestData.sampleTree2().getValueByKey(7));
		assertNull(EmptyPBST.getInstance().getValueByKey(2));
	}
	
	//tests adding an object to an emptyPBST object
	@Test public void studentTest4() {
		PBST<Integer,Character> tree = EmptyPBST.getInstance();
		tree = tree.addKeyValuePair(9, 'r');
		assertEquals(Character.valueOf('r'),tree.getValueByKey(9));
		assertEquals("9/r ",tree.toString());
		
	}
}
