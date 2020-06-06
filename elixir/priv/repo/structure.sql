--
-- PostgreSQL database dump
--

-- Dumped from database version 12.0 (Ubuntu 12.0-2.pgdg18.04+1)
-- Dumped by pg_dump version 12.0 (Ubuntu 12.0-2.pgdg18.04+1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: pgcrypto; Type: EXTENSION; Schema: -; Owner: -
--

CREATE EXTENSION IF NOT EXISTS pgcrypto WITH SCHEMA public;


--
-- Name: EXTENSION pgcrypto; Type: COMMENT; Schema: -; Owner: -
--

COMMENT ON EXTENSION pgcrypto IS 'cryptographic functions';


SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: companies; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.companies (
    name text NOT NULL,
    inserted_at timestamp with time zone DEFAULT now() NOT NULL,
    market_cap bigint NOT NULL,
    symbol text NOT NULL,
    updated_at timestamp with time zone DEFAULT now() NOT NULL,
    sector text DEFAULT public.gen_random_uuid() NOT NULL
);


--
-- Name: fund_transactions; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.fund_transactions (
    amount integer NOT NULL,
    description text NOT NULL,
    id integer NOT NULL,
    inserted_at timestamp with time zone DEFAULT now() NOT NULL,
    transacted_at timestamp with time zone NOT NULL,
    updated_at timestamp with time zone DEFAULT now() NOT NULL
);


--
-- Name: fund_transactions_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.fund_transactions_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: fund_transactions_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.fund_transactions_id_seq OWNED BY public.fund_transactions.id;


--
-- Name: schema_migrations; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.schema_migrations (
    version bigint NOT NULL,
    inserted_at timestamp(0) without time zone
);


--
-- Name: stock_buys; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.stock_buys (
    id integer NOT NULL,
    executed_at timestamp with time zone NOT NULL,
    inserted_at timestamp with time zone DEFAULT now() NOT NULL,
    price integer NOT NULL,
    symbol text NOT NULL,
    updated_at timestamp with time zone DEFAULT now() NOT NULL,
    volume integer NOT NULL
);


--
-- Name: stock_buys_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.stock_buys_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: stock_buys_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.stock_buys_id_seq OWNED BY public.stock_buys.id;


--
-- Name: stock_positions; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.stock_positions (
    inserted_at timestamp with time zone DEFAULT now() NOT NULL,
    stock_buy_id integer,
    stock_sell_id integer,
    updated_at timestamp with time zone DEFAULT now() NOT NULL,
    CONSTRAINT stock_positions_opening_trade_check CHECK (((((stock_buy_id IS NOT NULL))::integer + ((stock_sell_id IS NOT NULL))::integer) > 0))
);


--
-- Name: stock_quotes; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.stock_quotes (
    close double precision NOT NULL,
    date date NOT NULL,
    inserted_at timestamp with time zone DEFAULT now() NOT NULL,
    open double precision NOT NULL,
    symbol text NOT NULL,
    updated_at timestamp with time zone DEFAULT now() NOT NULL,
    volume bigint NOT NULL,
    id integer NOT NULL,
    beta double precision DEFAULT 1.0 NOT NULL
);


--
-- Name: stock_quotes_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.stock_quotes_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: stock_quotes_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.stock_quotes_id_seq OWNED BY public.stock_quotes.id;


--
-- Name: stock_sells; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.stock_sells (
    id integer NOT NULL,
    executed_at timestamp with time zone NOT NULL,
    inserted_at timestamp with time zone DEFAULT now() NOT NULL,
    price integer NOT NULL,
    symbol text NOT NULL,
    updated_at timestamp with time zone DEFAULT now() NOT NULL,
    volume integer NOT NULL
);


--
-- Name: stock_sells_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.stock_sells_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: stock_sells_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.stock_sells_id_seq OWNED BY public.stock_sells.id;


--
-- Name: fund_transactions id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.fund_transactions ALTER COLUMN id SET DEFAULT nextval('public.fund_transactions_id_seq'::regclass);


--
-- Name: stock_buys id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_buys ALTER COLUMN id SET DEFAULT nextval('public.stock_buys_id_seq'::regclass);


--
-- Name: stock_quotes id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_quotes ALTER COLUMN id SET DEFAULT nextval('public.stock_quotes_id_seq'::regclass);


--
-- Name: stock_sells id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_sells ALTER COLUMN id SET DEFAULT nextval('public.stock_sells_id_seq'::regclass);


--
-- Name: companies companies_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.companies
    ADD CONSTRAINT companies_pkey PRIMARY KEY (symbol);


--
-- Name: fund_transactions fund_transactions_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.fund_transactions
    ADD CONSTRAINT fund_transactions_pkey PRIMARY KEY (id);


--
-- Name: schema_migrations schema_migrations_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.schema_migrations
    ADD CONSTRAINT schema_migrations_pkey PRIMARY KEY (version);


--
-- Name: stock_buys stock_buys_executed_at_symbol_key; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_buys
    ADD CONSTRAINT stock_buys_executed_at_symbol_key UNIQUE (executed_at, symbol);


--
-- Name: stock_buys stock_buys_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_buys
    ADD CONSTRAINT stock_buys_pkey PRIMARY KEY (id);


--
-- Name: stock_quotes stock_quotes_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_quotes
    ADD CONSTRAINT stock_quotes_pkey PRIMARY KEY (id);


--
-- Name: stock_quotes stock_quotes_symbol_date_index; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_quotes
    ADD CONSTRAINT stock_quotes_symbol_date_index UNIQUE (date, symbol);


--
-- Name: stock_sells stock_sells_executed_at_symbol_key; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_sells
    ADD CONSTRAINT stock_sells_executed_at_symbol_key UNIQUE (executed_at, symbol);


--
-- Name: stock_sells stock_sells_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_sells
    ADD CONSTRAINT stock_sells_pkey PRIMARY KEY (id);


--
-- Name: companies_name_idx; Type: INDEX; Schema: public; Owner: -
--

CREATE INDEX companies_name_idx ON public.companies USING btree (name);


--
-- Name: companies_sector_idx; Type: INDEX; Schema: public; Owner: -
--

CREATE INDEX companies_sector_idx ON public.companies USING btree (sector);


--
-- Name: stock_positions_stock_buy_id_idx; Type: INDEX; Schema: public; Owner: -
--

CREATE UNIQUE INDEX stock_positions_stock_buy_id_idx ON public.stock_positions USING btree (stock_buy_id);


--
-- Name: stock_positions_stock_sell_id_idx; Type: INDEX; Schema: public; Owner: -
--

CREATE UNIQUE INDEX stock_positions_stock_sell_id_idx ON public.stock_positions USING btree (stock_sell_id);


--
-- Name: stock_buys stock_buys_symbol_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_buys
    ADD CONSTRAINT stock_buys_symbol_fkey FOREIGN KEY (symbol) REFERENCES public.companies(symbol);


--
-- Name: stock_positions stock_positions_stock_buy_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_positions
    ADD CONSTRAINT stock_positions_stock_buy_id_fkey FOREIGN KEY (stock_buy_id) REFERENCES public.stock_buys(id);


--
-- Name: stock_positions stock_positions_stock_sell_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_positions
    ADD CONSTRAINT stock_positions_stock_sell_id_fkey FOREIGN KEY (stock_sell_id) REFERENCES public.stock_sells(id);


--
-- Name: stock_quotes stock_quotes_symbol_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_quotes
    ADD CONSTRAINT stock_quotes_symbol_fkey FOREIGN KEY (symbol) REFERENCES public.companies(symbol);


--
-- Name: stock_sells stock_sells_symbol_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.stock_sells
    ADD CONSTRAINT stock_sells_symbol_fkey FOREIGN KEY (symbol) REFERENCES public.companies(symbol);


--
-- PostgreSQL database dump complete
--

INSERT INTO public."schema_migrations" (version) VALUES (20190516182826), (20190607210017), (20191217183105), (20191226180955), (20200102012459), (20200102023134), (20200102061635), (20200113170958);

