--
-- PostgreSQL database dump
--

-- Dumped from database version 9.6.10
-- Dumped by pg_dump version 9.6.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: _games; Type: TABLE; Schema: public; Owner: rebasedata
--

CREATE TABLE public._games (
    gametoken character varying(1) DEFAULT NULL::character varying,
    playergroup character varying(1) DEFAULT NULL::character varying,
    gametime character varying(1) DEFAULT NULL::character varying
);


ALTER TABLE public._games OWNER TO rebasedata;

--
-- Name: _messages; Type: TABLE; Schema: public; Owner: rebasedata
--

CREATE TABLE public._messages (
    messagetoken character varying(1) DEFAULT NULL::character varying,
    gametoken character varying(1) DEFAULT NULL::character varying,
    playergroup character varying(1) DEFAULT NULL::character varying,
    playerid character varying(1) DEFAULT NULL::character varying,
    "time" character varying(1) DEFAULT NULL::character varying
);


ALTER TABLE public._messages OWNER TO rebasedata;

--
-- Name: _playergroups; Type: TABLE; Schema: public; Owner: rebasedata
--

CREATE TABLE public._playergroups (
    playergroup character varying(1) DEFAULT NULL::character varying,
    playerid character varying(1) DEFAULT NULL::character varying
);


ALTER TABLE public._playergroups OWNER TO rebasedata;

--
-- Name: _players; Type: TABLE; Schema: public; Owner: rebasedata
--

CREATE TABLE public._players (
    playerid character varying(1) DEFAULT NULL::character varying,
    playertype character varying(1) DEFAULT NULL::character varying,
    playeraddr character varying(1) DEFAULT NULL::character varying,
    gametoken character varying(1) DEFAULT NULL::character varying
);


ALTER TABLE public._players OWNER TO rebasedata;

--
-- Data for Name: _games; Type: TABLE DATA; Schema: public; Owner: rebasedata
--

COPY public._games (gametoken, playergroup, gametime) FROM stdin;
\.


--
-- Data for Name: _messages; Type: TABLE DATA; Schema: public; Owner: rebasedata
--

COPY public._messages (messagetoken, gametoken, playergroup, playerid, "time") FROM stdin;
\.


--
-- Data for Name: _playergroups; Type: TABLE DATA; Schema: public; Owner: rebasedata
--

COPY public._playergroups (playergroup, playerid) FROM stdin;
\.


--
-- Data for Name: _players; Type: TABLE DATA; Schema: public; Owner: rebasedata
--

COPY public._players (playerid, playertype, playeraddr, gametoken) FROM stdin;
\.


--
-- PostgreSQL database dump complete
--

