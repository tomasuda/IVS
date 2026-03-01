//======= Copyright (c) 2026, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2025-02-19
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author TOM
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
TEST(SuffixAutomatEmpty,createAutomat){
    SuffixAutomaton automat;
    EXPECT_EQ(automat.size(),1); // automat should contain only initial state
}

TEST(SuffixAutomatEmpty,Contains){
    SuffixAutomaton automat;
    EXPECT_FALSE(automat.contains("a")); // automat should not contain 'a'
}

TEST(SuffixAutomatEmpty,Clear){
    SuffixAutomaton automat;
    automat.clear();
    EXPECT_EQ(automat.size(),1); // after clear, automat should contain only initial state
}

TEST(SuffixAutomatEmpty,AddElement){
    SuffixAutomaton automat;
    automat.add_element('a');
    EXPECT_EQ(automat.size(),2);// after adding 'a', automat should contain 2 states
    EXPECT_EQ(automat.contains("a"),true); // automat should contain 'a'
}

TEST(SuffixAutomatEmpty,AddSequence){
    SuffixAutomaton automat;
    automat.add_sequence("abc");
    EXPECT_EQ(automat.size(),4); // after adding "abc", automat should contain 4 states
    EXPECT_TRUE(automat.contains("a")); // automat should contain 'a'
    EXPECT_TRUE(automat.contains("b")); // automat should contain 'b'
    EXPECT_TRUE(automat.contains("c")); // automat should contain 'c'
}

TEST(SuffixAutomatEmpty,GetState){
    SuffixAutomaton automat;
    
    const State& init_state =automat.get_state(0);
    EXPECT_EQ(init_state.len,0);//initialstate should have length 0
    EXPECT_EQ(init_state.link,std::nullopt); // initial state should have no link
    EXPECT_EQ(init_state.next, (std::unordered_map<char, size_t>())); // initial state should have no transitions
    EXPECT_THROW(automat.get_state(1), std::out_of_range); // should throw std::out_of_range
}

TEST(SuffixAutomatEmpty,Step){
    SuffixAutomaton automat;
    size_t next_s;
    EXPECT_THROW(automat.step(1,'a',next_s), std::out_of_range); // should throw std::out_of_range
    EXPECT_THROW(automat.step(999, 'a', next_s), std::out_of_range); // should throw std::out_of_range
    EXPECT_FALSE(automat.step(0,'a',next_s)); // should return false for non-existent transition

}

TEST(SuffixAutomatEmpty,Next){
    SuffixAutomaton automat;
    EXPECT_THROW(automat.next(1), std::out_of_range); // should throw std::out_of_range
    EXPECT_THROW(automat.next(999), std::out_of_range); // should throw std::out_of_range

    EXPECT_TRUE(automat.next(0).empty()); // should return empty map for initial state
}
// this test resolves in failure
// deference between specification and implementation
TEST(SuffixAutomatEmpty,TopologicalSort){
    SuffixAutomaton automat;
    std::vector<size_t> topo_order = automat.topological_sort();
    EXPECT_EQ(topo_order.size(),1); // should contain only initial state
}

TEST(SuffixAutomatEmpty,LongestDirectContinuation){
    SuffixAutomaton automat;

    EXPECT_THROW(automat.longest_direct_continuation(1), std::out_of_range); // should throw std::out_of_range
    EXPECT_THROW(automat.longest_direct_continuation(999), std::out_of_range); // should throw std::out_of_range

    EXPECT_TRUE(automat.longest_direct_continuation(0).empty()); // should return empty string for initial state
}


TEST(SuffixAutomat,AddElement){
    SuffixAutomaton automat;
    automat.add_sequence("aaaaaabbbbbbbaaaabbbbbbsssbbsbsbsb");
    automat.add_element('g');
    EXPECT_EQ(automat.size(),56);// after adding 'g', automat should contain 56 states
    EXPECT_EQ(automat.contains("g"),true); // automat should contain 'g'
    automat.add_element('o');
    EXPECT_EQ(automat.size(),57); // after adding 'o', automat should contain 57 states 
    EXPECT_EQ(automat.contains("o"),true); // automat should contain 'o'
    automat.add_element('l');
    EXPECT_EQ(automat.size(),58); // after adding 'l', automat should contain 58 states 
    EXPECT_EQ(automat.contains("l"),true); // automat should contain 'l'
}

TEST(SuffixAutomat,Contains){
    SuffixAutomaton automat;
    EXPECT_FALSE(automat.contains("a")); // automat should not contain 'a'
    automat.add_element('a');
    EXPECT_TRUE(automat.contains("a")); // automat should contain 'a'
    EXPECT_FALSE(automat.contains("b")); // automat should not contain 'b'

    for(char c ='a'; c <= 'z'; ++c) automat.add_element(c);
    for(char c ='a'; c <= 'z'; ++c) EXPECT_TRUE(automat.contains(std::string(1,c))); // automat should contain all single character strings
    

    automat.add_sequence("abc");
    EXPECT_TRUE(automat.contains("abc")); // automat should contain "abc"
    EXPECT_FALSE(automat.contains("ac")); // automat should not contain "ac"
}
TEST(SuffixAutomat,Clear){
    SuffixAutomaton automat;
    automat.add_sequence("aaaaaabbbbbbbaaaabbbbbbsssbbsbsbsb");
    automat.clear();
    EXPECT_EQ(automat.size(),1); // after clear, automat should contain only initial state
}

TEST(SuffixAutomat,AddSequence){
    SuffixAutomaton automat;
    automat.add_sequence("abc");
    automat.add_sequence("def");
    EXPECT_EQ(automat.size(),7);

    std::string sequence(100, 'g');
    automat.add_sequence(sequence);
    EXPECT_GE(automat.size(), 107); // minimal length shoud be 107
    EXPECT_LE(automat.size(), 212); // can not have more then 2n states
    EXPECT_TRUE(automat.contains(sequence)); // automat should contain the long sequence
    EXPECT_TRUE(automat.contains("def")); // automat should contain def
    EXPECT_TRUE(automat.contains("abc")); // automat should contain abc
    EXPECT_TRUE(automat.contains("c")); // automat should contain c
    EXPECT_FALSE(automat.contains("tom")); // automat should not contain tom

}

TEST(SuffixAutomat,GetState){
    SuffixAutomaton automat;
    automat.add_element('a');
    const State& init_state =automat.get_state(0);
    EXPECT_EQ(init_state.len,0);//initialstate should have length 0
    EXPECT_EQ(init_state.link,std::nullopt); // initial state should have no link
    const State& state =automat.get_state(1);
    EXPECT_EQ(state.len ,1); // state should have len 1
    EXPECT_EQ(state.link,std::optional<size_t>(0)); // state should have link to initial state
    EXPECT_THROW(automat.get_state(2), std::out_of_range); // should throw std::out_of_range


    automat.add_element('b');
    const State& state2 =automat.get_state(2);
    const State& updated_state =automat.get_state(1);
    const State& updated_init_state =automat.get_state(0);
    EXPECT_EQ(state2.len ,2); // state should have len 2
    EXPECT_EQ(state2.link,std::optional<size_t>(0)); // state should have link to initial state
    EXPECT_EQ(state2.next.size(),0); // state should have no transitions
    EXPECT_EQ(updated_state.next,(std::unordered_map<char, size_t>{{'b',2}})); // updated state should have transition 'b' to state 2
    EXPECT_EQ(updated_init_state.next,(std::unordered_map<char, size_t>{{'a',1},{'b',2}})); // state should have transition 'a' to state 1
}

TEST(SuffixAutomat,GetStateLongSequence){
    SuffixAutomaton automat;
    automat.add_sequence("testsufix");
    const State& state =automat.get_state(0); //root state
    EXPECT_TRUE(state.next.count('t')); // root state should have transition 't'
    size_t t_state_index = state.next.at('t');
    const State& t_state = automat.get_state(t_state_index);
    EXPECT_EQ(t_state.len, 1); // state should have len 1
    
    // link should point to state with smaller len
    if(t_state.link.has_value()){
        size_t link_index = t_state.link.value();
        EXPECT_LT(automat.get_state(link_index).len, t_state.len); 
    }
}


TEST(SuffixAutomat,Step){
    SuffixAutomaton automat;

    automat.add_sequence("ab");
    size_t next_s;
    EXPECT_TRUE(automat.step(0,'a',next_s)); // should return true for existing transition
    EXPECT_EQ(next_s,1); // should transition to state 1

    EXPECT_TRUE(automat.step(0,'b',next_s));
    EXPECT_EQ(next_s,2); // should transition to state 2

    EXPECT_TRUE(automat.step(1,'b',next_s)); // should return true for existing transition
    EXPECT_EQ(next_s,2); // should transition to state 2
}

TEST(SuffixAutomat,StepLongSequence){
    SuffixAutomaton automat;
    automat.add_sequence("testsufix");
    size_t next_s;
    EXPECT_TRUE(automat.step(0,'t',next_s)); // should return true for existing transition
    EXPECT_EQ(next_s,1); // should transition to state 1

    EXPECT_TRUE(automat.step(next_s,'s',next_s)); // should return true for existing transition
    EXPECT_TRUE(automat.step(next_s,'u',next_s)); // should return true for existing transition
}

TEST(SuffixAutomat,Next){
    SuffixAutomaton automat;
    automat.add_sequence("ab");
    std::unordered_map<char, size_t> map = automat.next(0);
    EXPECT_EQ(map.size(),2); // should return map with 2 elements for initial state
    EXPECT_TRUE(map.count('a')); // should contain 'a'
    EXPECT_TRUE(map.count('b')); // should contain 'b'
}

TEST(SuffixAutomat,NextLongSequence){
    SuffixAutomaton automat;
    automat.add_sequence("testsufix");
    std::unordered_map<char, size_t> map = automat.next(0);
    EXPECT_TRUE(map.count('t')); // should contain 't'
    EXPECT_TRUE(map.count('s')); // should contain 's'

    map = automat.next(map.at('t'));
    EXPECT_TRUE(map.count('e')); // should contain 'e'
    EXPECT_TRUE(map.count('s')); // should contain 's'
}


TEST(SuffixAutomat,TopologicalSort){
    SuffixAutomaton automat;
    automat.add_sequence("ab");
    std::vector<size_t> topo_order = automat.topological_sort();
    EXPECT_EQ(topo_order.size(),3); // should contain 3 states (initial, a, b)
}

TEST(SuffixAutomat,LongestDirectContinuation){
    SuffixAutomaton automat;

    automat.add_element('a');
    std::string res;
    EXPECT_NO_THROW(res = automat.longest_direct_continuation(0));
    EXPECT_EQ(res, "a");
}


TEST(SuffixAutomat,LongestDirectContinuationLongSequence){
    SuffixAutomaton automat;
    automat.clear();
    automat.add_sequence("testsufixlong");
    const State& root_state =automat.get_state(0); // get root state

    EXPECT_NE(root_state.next.find('i'),root_state.next.end()); // root state should have transition 'i'
    size_t index_i = root_state.next.at('i'); // get state index for 'i'
    std::string res;
    EXPECT_NO_THROW(res = automat.longest_direct_continuation(index_i)); 
    EXPECT_EQ(res, "xlong"); // should return xlong for state i

}
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//

/*** Konec souboru white_box_tests.cpp ***/
