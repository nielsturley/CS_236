cmake_minimum_required(VERSION 3.16.3)
project(Project_4)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

file(COPY project3-exampleIO DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Project_4 main.cpp
        Parser.h
        Parser.cpp
        Rule.cpp
        Rule.h
        DatalogProgram.cpp
        DatalogProgram.h
        Parameter.cpp
        Parameter.h
        Predicate.cpp
        Predicate.h
        AddAutomaton.cpp
        AddAutomaton.h
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        CommaAutomaton.cpp
        CommaAutomaton.h
        FactsAutomaton.cpp
        FactsAutomaton.h
        FactsAutomaton.cpp
        FactsAutomaton.h
        IDAutomaton.cpp
        IDAutomaton.h
        Left_ParenAutomaton.cpp
        Left_ParenAutomaton.h
        Lexer.cpp
        Lexer.h
        MLCommentAutomaton.cpp
        MLCommentAutomaton.h
        MultiplyAutomaton.cpp
        MultiplyAutomaton.h
        PeriodAutomaton.cpp
        PeriodAutomaton.h
        Q_MarkAutomaton.cpp
        Q_MarkAutomaton.h
        QueriesAutomaton.cpp
        QueriesAutomaton.h
        Right_ParenAutomaton.cpp
        Right_ParenAutomaton.h
        RulesAutomaton.cpp
        RulesAutomaton.h
        SchemesAutomaton.cpp
        SchemesAutomaton.h
        SLCommentAutomaton.cpp
        SLCommentAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        Token.cpp
        Token.h
        UndefinedAutomaton.cpp
        UndefinedAutomaton.h Tuple.cpp Tuple.h Header.cpp Header.h Relation.cpp Relation.h Database.cpp Database.h Interpreter.cpp Interpreter.h)
