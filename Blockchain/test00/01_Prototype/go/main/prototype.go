package main

import (
	"bytes"
	"crypto/sha256"
	"fmt"
	"strconv"
	"time"
)

type Block struct {
	/* block headers */
	TimeStamp     int64  // 当前时间戳，即区块创建的时间
	PrevBlockHash []byte // 前一个区块的Hash
	Hash          []byte // 当前区块的Hash
	/* body */
	Data []byte // 区块实际存储的信息, 即比特币中的 Transaction
}

func (b *Block) SetHash() {
	timestamp := []byte(strconv.FormatInt(b.TimeStamp, 10))

	headers := bytes.Join([][]byte{b.PrevBlockHash, b.Data, timestamp}, []byte{})

	// fmt.Printf("prev hash:\t%s\n", b.PrevBlockHash)
	// fmt.Printf("data:\t%s\n", b.Data)
	// fmt.Printf("ts:\t%x\n", timestamp)

	fmt.Printf("headers:\t%s\n", headers)
	hash := sha256.Sum256(headers)
	b.Hash = hash[:]
}

func NewBlock(data string, prevBlockHash []byte) *Block {
	block := &Block{
		TimeStamp: time.Now().Unix(),
		// TimeStamp:     0,
		PrevBlockHash: prevBlockHash,
		Hash:          []byte{},
		Data:          []byte(data)}
	// fmt.Printf("prev hash:\t%x\n", prevBlockHash)
	block.SetHash()
	return block
}

type BlockChain struct {
	blocks []*Block
}

//
func (bc *BlockChain) AddBlock(data string) {
	prevBlock := bc.blocks[len(bc.blocks)-1]
	// fmt.Printf("prev hash:\t%x\n", prevBlock.Hash)
	// fmt.Printf("curr data:\t%s\n", data)
	newBlock := NewBlock(data, prevBlock.Hash)

	bc.blocks = append(bc.blocks, newBlock)
}

func NewGenesisBlock() *Block {
	return NewBlock("Genesis Block", []byte{})
}

func NewBlockChain() *BlockChain {
	return &BlockChain{[]*Block{NewGenesisBlock()}}
}

func main() {
	bc := NewBlockChain()

	bc.AddBlock("send 1 BTC to Ivan")
	bc.AddBlock("send 2 more BTC to Ivan")

	for _, block := range bc.blocks {
		fmt.Printf("Prev hash: %x\n", block.PrevBlockHash)
		fmt.Printf("Data: %s\n", block.Data)
		fmt.Printf("Hash: %x\n", block.Hash)
		fmt.Println()
	}
}
